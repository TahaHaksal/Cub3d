#include "../headers/cub3d.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->ll + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_square(t_img *img, double x, double y, int colour)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP_GRID)
	{
		j = 0;
		while (j < MINIMAP_GRID)
		{
			my_mlx_pixel_put(img, (MINIMAP_GRID * x) + i, \
				(MINIMAP_GRID * y) + j, colour);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_img *img, t_game *game, t_player *player, t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->row)
	{
		j = 0;
		while (game->grid[i][j])
		{
			if (game->grid[i][j] == '1')
				draw_square(img, j, i, get_trgb(149, 255, 0, 0));
			else if (game->grid[i][j] == '0')
				draw_square(img, j, i, 0x95FFFFFF);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->window, img->img, 0, 0);
	draw_square(img, player->pos.x, player->pos.y, 0x9500FF00);
	mlx_put_image_to_window(mlx->mlx, mlx->window, img->img, 0, 0);
}

/*
	@param len of the wall
	@param texture index
	@param ray info
	@param player info
*/
int	pick_tex_x(int len, int i, t_rayVals ray, t_player *p, t_game *game)
{
	double	wallX;
	int		texX;
	int		texW;

	texW = game->image_sizes[i].x;
	if (ray.wall.y == 0)
		wallX = p->pos.y - ray.wall.x * ray.rayDir.y;
	else
		wallX = p->pos.x + ray.wall.x * ray.rayDir.x;
	wallX -= floor(wallX);
	texX = (wallX * (double)(texW));
	if(ray.wall.y == 0 && ray.rayDir.x > 0)
		texX = texW - texX - 1;
	if(ray.wall.y == 1 && ray.rayDir.y < 0)
		texX = texW - texX - 1;
	return (texX);
}

t_v	calc_DDA(t_mlx *mlx, t_v map, t_v sideDist, t_v step, t_v deltaDist)
{
	int		hit;
	int		side;
	double	perpWallDist;

 	hit = 0;
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

void	draw_walls(int x, t_rayVals *d, t_img *img, t_mlx *mlx)
{
	t_i	wall;
	t_i	heights;
	int	wallHeight;
	int	texX;
	int	lH;

	lH = (int)(HEIGHT / d->wall.x);
	wall.x = -lH / 3 + HEIGHT / 2;
	if (wall.x < 0)
		wall.x = 0;
	wall.y = lH / 3 + HEIGHT / 2;
	if (wall.y > HEIGHT)
		wall.y = HEIGHT - 1;
	wallHeight = wall.y - wall.x;
	heights.x = mlx->game->image_sizes[1].y;
	heights.y = lH;
	texX = pick_tex_x(x, 1, *d, mlx->player, mlx->game);
	if (d->wall.y > 0 && d->rayDir.y > 0)
		vert_line (x, wall, img, texX, heights, &mlx->game->textures[1]);
	else if (d->wall.y > 0)
		vert_line (x, wall, img, texX, heights, &mlx->game->textures[0]);
	else if (d->rayDir.x > 0)
		vert_line(x, wall, img, texX, heights, &mlx->game->textures[2]);
	else
		vert_line(x, wall, img, texX, heights, &mlx->game->textures[3]);
}

void	draw_scene(t_img *img, t_game *game, t_player *player, t_mlx *mlx)
{
	t_rayVals	*d;
	int			x;
	int		wallStart;
	int		wallEnd;
	double	cameraX;

	x = -1;
	d = player->d;
	while (++x < WIDTH)
	{
		cameraX = 2 * x / (double)WIDTH - 1;
		d->rayDir.x = (player->dir.x + player->plane.x * cameraX) + 0.000001;
		d->rayDir.y = (player->dir.y + player->plane.y * cameraX) + 0.000001;
		calc_delta_dist(d->rayDir, &d->delta);
		d->map.x = (int)player->pos.x;
		d->map.y = (int)player->pos.y;
		calc_sides(player);
		d->wall = calc_DDA(mlx, d->map, d->side, d->step, d->delta);
		draw_walls(x, d, img, mlx);
	}
}

void	draw_map(t_mlx *mlx)
{
	int	median = HEIGHT / 2, y = -1, x;

	while (++y < median)
	{
		x = -1;
		while (++x < WIDTH)
			my_mlx_pixel_put(mlx->image, x, y, mlx->game->ceiling);
	}
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			my_mlx_pixel_put(mlx->image, x, y, mlx->game->floor);
	}
	draw_scene(mlx->image, mlx->game, mlx->player, mlx);
	draw_minimap(mlx->image, mlx->game, mlx->player, mlx);
}
