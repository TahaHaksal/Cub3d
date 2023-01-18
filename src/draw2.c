#include "../headers/cub3d.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, unsigned int color)
{
	char	*dst;

	dst = data->addr + (y * data->ll + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
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

void	draw_ceil_and_floor(t_mlx *mlx, int x, int y)
{
	while (++y < (HEIGHT / 2))
	{
		x = -1;
		while (++x < WIDTH)
		{
			my_mlx_pixel_put(mlx->image, x, y, mlx->game->ceiling);
			my_mlx_pixel_put(mlx->image, x, y + HEIGHT / 2, mlx->game->floor);
		}
	}
}

int	pick_dir(t_v wall, t_v ray_dir)
{
	if (wall.y > 0 && ray_dir.y > 0)
		return (1);
	else if (wall.y > 0)
		return (0);
	else if (ray_dir.x > 0)
		return (2);
	return (3);
}

int	pick_tex_x(int i, t_rayVals ray, t_player *p, t_game *game)
{
	double	wall_x;
	int		tex_x;
	int		tex_w;

	tex_w = game->image_sizes[i].x;
	if (ray.wall.y == 0)
		wall_x = p->pos.y - ray.wall.x * ray.rayDir.y;
	else
		wall_x = p->pos.x + ray.wall.x * ray.rayDir.x;
	wall_x -= floor(wall_x);
	tex_x = (wall_x * (double)(tex_w));
	if (ray.wall.y == 0 && ray.rayDir.x > 0)
		tex_x = tex_w - tex_x - 1;
	if (ray.wall.y == 1 && ray.rayDir.y < 0)
		tex_x = tex_w - tex_x - 1;
	return (tex_x);
}
