#include "../headers/cub3d.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_square(t_img *img, double x, double y, int colour)
{
	int (i) = -1;
	int	j;

	while (++i < MINIMAP_GRID - 1)
	{
		j = 0;
		while (j < MINIMAP_GRID - 1)
			my_mlx_pixel_put(img, (MINIMAP_GRID * x) + i, (MINIMAP_GRID * y) + j++, colour);
	}
}

void	draw_minimap(t_img *img, t_game *game, t_player *player, t_mlx *mlx)
{
	for (int i = 0 ; i < game->row ; i++)
	{
		for (int j = 0 ; game->grid[i][j]; j++)
		{
			if (game->grid[i][j] == '1')
				draw_square(img, j, i, get_trgb(125, 255, 0, 0));
			else if (game->grid[i][j] == '0')
				draw_square(img, j, i, get_trgb(125, 255, 255, 255));
		}
	}
	for (int x = 0 ; x < WIDTH ; x++)
	{
		double	cameraX = 2 * x / (double) WIDTH - 1;
		t_v		rayDir;
		t_v		temp;
		t_v		temp2;

		rayDir.x = player->dir.x + player->plane.x * cameraX;
		rayDir.y = player->dir.y + player->plane.y * cameraX;
		temp.x = MINIMAP_GRID * player->pos.x;
		temp.y = MINIMAP_GRID * player->pos.y;
		temp2.x = player->pos.x * MINIMAP_GRID + 2 * (rayDir.x * MINIMAP_GRID);
		temp2.y = player->pos.y * MINIMAP_GRID + 2 * (-rayDir.y * MINIMAP_GRID);

		diagonal_line(temp, temp2, img, mlx);
	}
	draw_square(img, player->pos.x, player->pos.y, get_trgb(16, 0, 255, 0));
}

t_v		calc_DDA(t_mlx *mlx, t_v map, t_v sideDist, t_v step, t_v deltaDist)
{
	int (hit) = 0;
	int		side;
	double	perpWallDist;

	while (hit == 0)
	{
		if (sideDist.x < sideDist.y)
		{
			sideDist.x += deltaDist.x;
			map.x += step.x;
			side = 0;
		}
		else
		{
			sideDist.y += deltaDist.y;
			map.y += step.y;
			side = 1;
		}
		if (mlx->game->grid[(int)(map.y)][(int)(map.x)] == '1')
			hit = 1;
	}
	if (side == 0)
		perpWallDist = sideDist.x - deltaDist.x;
	else
		perpWallDist = sideDist.y - deltaDist.y;
	return ((t_v){.x = perpWallDist, .y = side});
}

void	calc_delta_dist(t_v raydir, t_v *delta_dist)
{
	if (raydir.y == 0)
		delta_dist->x = 0;
	else
	{
		if (raydir.x == 0)
			delta_dist->x = 1;
		else
			delta_dist->x = fabs(1 / raydir.x);
	}
	if (raydir.x == 0)
		delta_dist->y = 0;
	else
	{
		if (raydir.y == 0)
			delta_dist->y = 1;
		else
			delta_dist->y = fabs(1 / raydir.y);
	}
}

void	calc_sides(t_player *player)
{
	t_rayVals	*d;

	d = player->d;
	if (d->rayDir.x < 0)
	{
		d->step.x = -1;
		d->side.x = (player->pos.x - d->map.x) * d->delta.x;
	}
	else
	{
		d->step.x = 1;
		d->side.x = (d->map.x + 1.0 - player->pos.x) * d->delta.x;
	}
	if (d->rayDir.y < 0)
	{
		d->step.y = 1;
		d->side.y = (d->map.y + 1.0 - player->pos.y) * d->delta.y;
	}
	else
	{
		d->step.y = -1;
		d->side.y = (player->pos.y - d->map.y) * d->delta.y;
	}
}

void	draw_walls(int x, t_rayVals *d, t_img *img)
{
	int	wallStart;
	int	wallEnd;
	int	transparan;

	transparan = d->wall.x * 20;
	if (transparan > 255)
		transparan = 255;
	d->wall.x = HEIGHT / d->wall.x;
	wallStart = -d->wall.x / 3 + HEIGHT / 2;
	if (wallStart < 0)
		wallStart = 0;
	wallEnd = d->wall.x / 3 + HEIGHT / 2;
	if (wallEnd >= HEIGHT)
		wallEnd = HEIGHT - 1;
	if (d->wall.y > 0 && d->rayDir.y > 0) //Güney
		vert_line (x, wallStart, wallEnd, img, get_trgb(transparan, 1, 13, 141));
	else if (d->wall.y > 0) //Kuzey
		vert_line(x, wallStart, wallEnd, img, get_trgb(transparan, 134, 100, 71));
	else if (d->rayDir.x > 0) //Batı
		vert_line (x, wallStart, wallEnd, img, get_trgb(transparan, 104, 17, 10));
	else //Doğu
		vert_line(x, wallStart, wallEnd, img, get_trgb(transparan, 195, 193, 196));
}

void	draw_scene(t_img *img, t_game *game, t_player *player, t_mlx *mlx)
{
	int (x) = 0;
	t_rayVals	*d;
	int			wallStart;
	int			wallEnd;
	double		cameraX;

	d = player->d;
	while (x++ < WIDTH)
	{
		cameraX = 2 * x / (double)WIDTH - 1;
		d->rayDir.x = player->dir.x + player->plane.x * cameraX;
		d->rayDir.y = player->dir.y + player->plane.y * cameraX;
		calc_delta_dist(d->rayDir, &d->delta);
		d->map.x = (int)player->pos.x;
		d->map.y = (int)player->pos.y;
		calc_sides(player);
		d->wall = calc_DDA(mlx, d->map, d->side, d->step, d->delta);
		draw_walls(x, player->d, img);
	}
}

void	draw_target(t_mlx *mlx)
{
	mlx_pixel_put(mlx->mlx, mlx->window, 899, 540, get_trgb(0, 25, 255, 25));
	mlx_pixel_put(mlx->mlx, mlx->window, 899, 541, get_trgb(0, 25, 255, 25));
	mlx_pixel_put(mlx->mlx, mlx->window, 900, 540, get_trgb(0, 25, 255, 25));
	mlx_pixel_put(mlx->mlx, mlx->window, 900, 541, get_trgb(0, 25, 255, 25));

	mlx_pixel_put(mlx->mlx, mlx->window, 903, 536, get_trgb(0, 25, 255, 25));
	mlx_pixel_put(mlx->mlx, mlx->window, 903, 537, get_trgb(0, 25, 255, 25));
	mlx_pixel_put(mlx->mlx, mlx->window, 904, 536, get_trgb(0, 25, 255, 25));
	mlx_pixel_put(mlx->mlx, mlx->window, 904, 537, get_trgb(0, 25, 255, 25));

	mlx_pixel_put(mlx->mlx, mlx->window, 903, 544, get_trgb(0, 25, 255, 25));
	mlx_pixel_put(mlx->mlx, mlx->window, 903, 545, get_trgb(0, 25, 255, 25));
	mlx_pixel_put(mlx->mlx, mlx->window, 904, 544, get_trgb(0, 25, 255, 25));
	mlx_pixel_put(mlx->mlx, mlx->window, 904, 545, get_trgb(0, 25, 255, 25));

	mlx_pixel_put(mlx->mlx, mlx->window, 907, 540, get_trgb(0, 25, 255, 25));
	mlx_pixel_put(mlx->mlx, mlx->window, 907, 541, get_trgb(0, 25, 255, 25));
	mlx_pixel_put(mlx->mlx, mlx->window, 908, 540, get_trgb(0, 25, 255, 25));
	mlx_pixel_put(mlx->mlx, mlx->window, 908, 541, get_trgb(0, 25, 255, 25));
}

void	draw_ceil_and_floor(t_mlx *mlx, int	x, int y)
{
	while (++y < (HEIGHT / 2))
	{
		x = -1;
		while (++x < WIDTH)
		{
			my_mlx_pixel_put(mlx->image, x, y, mlx->game->ceiling); // Bir tavan
			my_mlx_pixel_put(mlx->image, x, y + HEIGHT / 2, mlx->game->floor); // Bir zemin basıyor
		}
	}
}

int	draw_map(t_mlx *mlx)
{
	mlx_clear_window(mlx->mlx, mlx->window);
	draw_ceil_and_floor(mlx, -1, -1);
	draw_scene(mlx->image, mlx->game, mlx->player, mlx);
	if (mlx->game->miniMap % 2)
		draw_minimap(mlx->image, mlx->game, mlx->player, mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->image->img, 0, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->game->weapon, 700, 700);
	draw_target(mlx);
	return (0);
}
