#include "../headers/cub3d.h"

void	draw_square(t_img *img, double x, double y, int colour)
{
	int	i;
	int	j;

	i = -1;
	while (++i < MINIMAP_GRID - 1)
	{
		j = -1;
		while (++j < MINIMAP_GRID - 1)
			my_mlx_pixel_put(img, (MINIMAP_GRID * x) + i, \
				(MINIMAP_GRID * y) + j, colour);
	}
}

void	draw_minimap(t_img *img, t_game *game, t_player *player, t_mlx *mlx)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->row)
	{
		j = -1;
		while (game->grid[i][++j])
		{
			if (game->grid[i][j] == '1')
				draw_square(img, j, i, get_trgb(149, 255, 0, 0));
			else if (game->grid[i][j] == '0')
				draw_square(img, j, i, 0x95FFFFFF);
		}
	}
	calc_diagonal_line(img, player, mlx);
	draw_square(img, player->pos.x, player->pos.y, 0x9500FF00);
}

void	draw_walls(int x, t_rayVals *d, t_img *img, t_mlx *mlx)
{
	t_img		*t;
	t_draw_wall	e;
	int			i;

	i = pick_dir(d->wall, d->rayDir);
	t = mlx->game->textures;
	e.l_h = (int)(HEIGHT / d->wall.x);
	e.wall_mn = -e.l_h / 3 + HEIGHT / 2;
	if (e.wall_mn < 0)
		e.wall_mn = 0;
	e.wall_mx = e.l_h / 3 + HEIGHT / 2;
	if (e.wall_mx > HEIGHT)
		e.wall_mx = HEIGHT - 1;
	e.t_h = mlx->game->image_sizes[i].y;
	e.t_w = mlx->game->image_sizes[i].x;
	e.tex_x = pick_tex_x(i, *d, mlx->player, mlx->game);
	vert_line(x, img, &t[i], e);
}

void	draw_scene(t_img *img, t_game *game, t_player *player, t_mlx *mlx)
{
	t_rayVals	*d;
	double		camera_x;

	d = player->d;
	int (x) = 0;
	while (x < WIDTH)
	{
		camera_x = 2 * x / (double)WIDTH - 1;
		d->rayDir.x = (player->dir.x + player->plane.x * camera_x) + 0.000001;
		d->rayDir.y = (player->dir.y + player->plane.y * camera_x) + 0.000001;
		calc_delta_dist(d->rayDir, &d->delta);
		d->map.x = (int)player->pos.x;
		d->map.y = (int)player->pos.y;
		calc_sides(player);
		d->wall = calc_dda(mlx, d->map, d->side, *d);
		draw_walls(x, player->d, img, mlx);
		x++;
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
