/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ddacalculator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarhan <dkarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 08:54:37 by mhaksal           #+#    #+#             */
/*   Updated: 2023/01/20 12:01:56 by dkarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

t_v	calc_dda(t_mlx *mlx, t_v map, t_v sideDist, t_rayVals step_dd)
{
	int		side;
	double	perp_wall_dist;

	int (hit) = 0;
	while (hit == 0)
	{
		if (sideDist.x < sideDist.y)
		{
			sideDist.x += step_dd.delta.x;
			map.x += step_dd.step.x;
			side = 0;
		}
		else
		{
			sideDist.y += step_dd.delta.y;
			map.y += step_dd.step.y;
			side = 1;
		}
		if (mlx->game->grid[(int)(map.y)][(int)(map.x)] == '1')
			hit = 1;
	}
	perp_wall_dist = sideDist.y - step_dd.delta.y;
	if (side == 0)
		perp_wall_dist = sideDist.x - step_dd.delta.x;
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
	if (d->ray_dir.x < 0)
	{
		d->step.x = -1;
		d->side.x = (player->pos.x - d->map.x) * d->delta.x;
	}
	else
	{
		d->step.x = 1;
		d->side.x = (d->map.x + 1.0 - player->pos.x) * d->delta.x;
	}
	if (d->ray_dir.y < 0)
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

void	calc_diagonal_line(t_img *img, t_player *player, t_mlx *mlx)
{
	t_v		raydir;
	t_v		temp;
	t_v		temp2;
	double	camera_x;

	int (i) = 0;
	while (i < WIDTH)
	{
		camera_x = (2 * i) / (double) WIDTH - 1;
		raydir.x = player->dir.x + player->plane.x * camera_x;
		raydir.y = player->dir.y + player->plane.y * camera_x;
		temp.x = MINIMAP_GRID * player->pos.x;
		temp.y = MINIMAP_GRID * player->pos.y;
		temp2.x = player->pos.x * MINIMAP_GRID + 2 * (raydir.x * MINIMAP_GRID);
		temp2.y = player->pos.y * MINIMAP_GRID + 2 * (-raydir.y * MINIMAP_GRID);
		diagonal_line(temp, temp2, img, mlx);
		i++;
	}
}
