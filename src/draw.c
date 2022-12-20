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

double	calc_DDA(t_mlx *mlx, t_v map, t_v sideDist, t_v step, t_v deltaDist)
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
		if (mlx->game->grid[(int)map.y][(int)map.x] == '1')
			hit = 1;
	}
	if (side == 0)
		perpWallDist = fabs(sideDist.x - deltaDist.x);
	else
		perpWallDist = fabs(sideDist.y - deltaDist.y);
	return (perpWallDist);
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

void	draw_scene(t_img *img, t_game *game, t_player *player, t_mlx *mlx)
{
	for (int x = 0; x < WIDTH; x++)
	{
		//Ray yönü
		double	cameraX = 2 * x / (double) WIDTH - 1;
		t_v		rayDir;

		//Rayin x veya y yönünden bir sonraki x veya y yönüne uzaklığı
		t_v		deltaDist;

		//İlerlenecek kutunun yönü (örn sağ kutuya gidilecekse step.x = 1)
		t_v		step;

		//Bulunulan konumdan bir sonraki x veya y duvarına uzaklık
		t_v		sideDist;

		//Haritanın hangi gridinde olduğunu söylüyor.
		t_v		map;

		double	wallDist;
		int		wallStart;
		int		wallEnd;

		// printf("%f\n", cameraX);
		rayDir.x = player->dir.x + player->plane.x * cameraX;
		rayDir.y = player->dir.y + player->plane.y * cameraX;


		// deltaDist.x = (rayDir.x == 0) ? 1e30 : fabs(1.0 / rayDir.x);
		// deltaDist.y = (rayDir.y == 0) ? 1e30 : fabs(1.0 / rayDir.y);
		calc_delta_dist(rayDir, &deltaDist);

		map.x = (int)player->pos.x;
		map.y = (int)player->pos.y;

		if (rayDir.x < 0)
		{
			step.x = -1;
			sideDist.x = (player->pos.x - map.x) * deltaDist.x;
		}
		else
		{
			step.x = 1;
			sideDist.y = (map.x + 1.0 - player->pos.x) * deltaDist.x;
		}
		if (rayDir.y < 0)
		{
			step.y = 1;
			sideDist.y = (map.y + 1.0 - player->pos.y) * deltaDist.y;
		}
		else
		{
			step.y = -1;
			sideDist.y = (player->pos.y - map.y) * deltaDist.y;
		}
		//DDA hesaplanıyor duvar mesafesi alınıyor.
		wallDist = calc_DDA(mlx, map, sideDist, step, deltaDist);
		wallDist = HEIGHT / wallDist;

		//duvarın çizilmeye başlayacağı konum
		wallStart = -wallDist / 2 + HEIGHT / 2;
		if (wallStart < 0)
			wallStart = 0;

		//duvarın çizilmeyi bitireceği konum
		wallEnd = wallDist / 2 + HEIGHT / 2;
		if (wallEnd >= HEIGHT)
			wallEnd = HEIGHT - 1;

		//dikey çizgi çiziyor
		vert_line (x, wallStart, wallEnd, img);
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
