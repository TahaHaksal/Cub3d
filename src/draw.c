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
				draw_square(img, j, i, get_trgb(0, 255, 0, 0));
			else if (game->grid[i][j] == '0')
				draw_square(img, j, i, 0x00FFFFFF);
		}
	}
	draw_square(img, player->x, player->y, 0x0000FF00);
	mlx_put_image_to_window(mlx->mlx, mlx->window, img->img, 0, 0);
}

void	draw_map(t_img *img, t_game *game, t_player *player, t_mlx *mlx)
{
	int	median = HEIGHT / 2, y = -1, x;

	while (++y < median)
	{
		x = -1;
		while (++x < WIDTH)
			my_mlx_pixel_put(img, x, y, 0XAB4F94CD);
	}	
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			my_mlx_pixel_put(img, x, y, 0XAB4BA123);
	}
}