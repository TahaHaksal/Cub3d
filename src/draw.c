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
	@param i texture indexi
	@param ray ray değerlerimiz
	@param p player değerlerimiz
	@param game oyun bilgilerimiz
*/
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

t_v	calc_dda(t_mlx *mlx, t_rayVals d)
{
	int		hit;
	int		side;
	double	perp_wall_dist;

	hit = 0;
	while (hit == 0)
	{
		if (d.side.x < d.side.y)
		{
			d.side.x += d.delta.x;
			d.map.x += d.step.x;
			side = 0;
		}
		else
		{
			d.side.y += d.delta.y;
			d.map.y += d.step.y;
			side = 1;
		}
		if (mlx->game->grid[(int)(d.map.y)][(int)(d.map.x)] == '1')
			hit = 1;
	}
	if (side == 0)
		perp_wall_dist = d.side.x - d.delta.x;
	else
		perp_wall_dist = d.side.y - d.delta.y;
	return ((t_v){.x = perp_wall_dist, .y = side});
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

/*
	@param which side the wall was hit
	@param ray direction
	@returns index for textures
*/
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
	int			x;
	double		camera_x;

	x = -1;
	d = player->d;
	while (++x < WIDTH)
	{
		camera_x = 2 * x / (double)WIDTH - 1;
		d->rayDir.x = (player->dir.x + player->plane.x * camera_x) + 0.000001;
		d->rayDir.y = (player->dir.y + player->plane.y * camera_x) + 0.000001;
		calc_delta_dist(d->rayDir, &d->delta);
		d->map.x = (int)player->pos.x;
		d->map.y = (int)player->pos.y;
		calc_sides(player);
		d->wall = calc_dda(mlx, *d);
		draw_walls(x, d, img, mlx);
	}
}

void	draw_map(t_mlx *mlx)
{
	int	median;
	int	y;
	int	x;

	median = HEIGHT / 2;
	y = -1;
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
