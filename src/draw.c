#include "../headers/cub3d.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
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
			my_mlx_pixel_put(img, (MINIMAP_GRID * x) + i, (MINIMAP_GRID * y) + j, colour);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_img *img, t_game *game, t_player *player, t_mlx *mlx)
{
	// printf("x: %f	y: %f\n", mlx->player.x, mlx->player.y); // -> Kameranın konumu
	for (int i = 0; game->grid[i]; i++)
	{
		for (int j = 0; game->grid[i][j]; j++)
		{
			if (game->grid[i][j] == '1')
				draw_square(img, j, i, get_trgb(149, 255, 0, 0));
			else if (game->grid[i][j] == '0')
				draw_square(img, j, i, 0x95FFFFFF);
		}
	}
	draw_square(img, player->pos.x, player->pos.y, 0x9500FF00);
	mlx_put_image_to_window(mlx->mlx, mlx->window, img->img, 0, 0);
}

void	calc_DDA(t_game *game, t_v map, t_v sideDist, t_v step, t_v deltaDist)
{
	int		hit;
	int		side;
	double	perpWallDist;

	hit = 0;
	while (hit == 0)
	{
		//jump to next map square, either in x-direction, or in y-direction
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
		//Check if ray has hit a wall
		if (game->grid[(int)map.y][(int)map.x] == '1')
			hit = 1;
	}
	if (side == 0)
		perpWallDist = (sideDist.x - deltaDist.x);
	else
		perpWallDist = (sideDist.y - deltaDist.y);
	printf("WallDist: %f\n", perpWallDist);
}

void	draw_scene(t_img *img, t_game *game, t_player *player, t_mlx *mlx)
{
	for (int x = 0; x < WIDTH; x++)
	{
		double	cameraX = 2 * x / (double) WIDTH - 1;
		t_v		rayDir;
		//length of ray from one x or y-side to next x or y-side
		t_v		deltaDist;
		//what direction to step in x or y-direction (either +1 or -1)
		t_v		step;
		//length of ray from current position to next x or y-side
		t_v		sideDist;
		//which box of the map we're in
		t_v		map;

		rayDir.x = player->dir.x + player->plane.x * (2 * x / (double)WIDTH - 1);
		rayDir.y = player->dir.y + player->plane.y * (2 * x / (double)WIDTH - 1);
		deltaDist.x = fabs(1.0 / rayDir.x);
		deltaDist.y = fabs(1.0 / rayDir.y);
		map.x = (int)player->pos.x;
		map.y = (int)player->pos.y;
		sideDist.x = 0;
		sideDist.y = 0;
		if (rayDir.x < 0)
		{
			step.x = -1;
			sideDist.x = (player->pos.x - floor(player->pos.x)) * deltaDist.x;
			// printf("SideDist.x = %f\n", sideDist.x);
		}
		else
		{
			step.x = 1;
			sideDist.y = (floor(player->pos.x) + 1.0 - player->pos.x) * deltaDist.x;
			// printf("SideDist.x = %f\n", sideDist.x);
		}
		if (rayDir.y < 0)
		{
			step.y = -1;
			sideDist.y = (player->pos.x - floor(player->pos.x)) * deltaDist.y;
			// printf("SideDist.y = %f\n", sideDist.y);
		}
		else
		{
			step.y = 1;
			sideDist.y = (floor(player->pos.y) + 1.0 - player->pos.y) * deltaDist.y;
			// printf("SideDist.y = %f\n", sideDist.y);
		}
		//perform DDA
		calc_DDA(game, map, sideDist, step, deltaDist);
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
}
