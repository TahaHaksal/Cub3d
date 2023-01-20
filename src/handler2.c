/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaksal <mhaksal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 08:54:52 by mhaksal           #+#    #+#             */
/*   Updated: 2023/01/20 08:54:53 by mhaksal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	calc_rotation(t_player *player, char sign)
{
	double	dx;
	double	planex;
	double	rot_spd;

	rot_spd = -ROT_SPEED;
	if (sign == 'l')
		rot_spd = ROT_SPEED;
	dx = player->dir.x;
	planex = player->plane.x;
	player->dir.x = dx * cosf(rot_spd) - player->dir.y * sinf(rot_spd);
	player->dir.y = dx * sinf(rot_spd) + player->dir.y * cosf(rot_spd);
	player->plane.x = planex * cosf(rot_spd) - player->plane.y * sinf(rot_spd);
	player->plane.y = planex * sinf(rot_spd) + player->plane.y * cosf(rot_spd);
}

void	calc_movement_f(t_mlx *mlx)
{
	double	px;
	double	py;
	double	dx;
	double	dy;

	px = mlx->player->pos.x;
	py = mlx->player->pos.y;
	dx = mlx->player->dir.x;
	dy = mlx->player->dir.y;
	if (mlx->game->grid[(int)(py)][(int)(px + dx * MOV_SPEED)] == '0')
		mlx->player->pos.x += dx * MOV_SPEED;
	if (mlx->game->grid[(int)(py - dy * MOV_SPEED)][(int)(px)] == '0')
		mlx->player->pos.y -= dy * MOV_SPEED;
}

void	calc_movement_b(t_mlx *mlx)
{
	double	px;
	double	py;
	double	dx;
	double	dy;

	px = mlx->player->pos.x;
	py = mlx->player->pos.y;
	dx = mlx->player->dir.x;
	dy = mlx->player->dir.y;
	if (mlx->game->grid[(int)(py)][(int)(px - dx * MOV_SPEED)] == '0')
		mlx->player->pos.x -= dx * MOV_SPEED;
	if (mlx->game->grid[(int)(py + dy * MOV_SPEED)][(int)(px)] == '0')
		mlx->player->pos.y += dy * MOV_SPEED;
}

void	calc_movement_l(t_mlx *mlx)
{
	double	px;
	double	py;
	double	dx;
	double	dy;

	px = mlx->player->pos.x;
	py = mlx->player->pos.y;
	dx = mlx->player->dir.x;
	dy = mlx->player->dir.y;
	if (mlx->game->grid[(int)(py - dx * MOV_SPEED)][(int)(px)] == '0')
	{
		mlx->player->pos.y -= dx * MOV_SPEED;
		py = mlx->player->pos.y;
	}
	if (mlx->game->grid[(int)(py)][(int)(px - dy * MOV_SPEED)] == '0')
		mlx->player->pos.x -= dy * MOV_SPEED;
}

void	calc_movement_r(t_mlx *mlx)
{
	double	px;
	double	py;
	double	dx;
	double	dy;

	px = mlx->player->pos.x;
	py = mlx->player->pos.y;
	dx = mlx->player->dir.x;
	dy = mlx->player->dir.y;
	if (mlx->game->grid[(int)(py)][(int)(px + dy * MOV_SPEED)] == '0')
		mlx->player->pos.x += dy * MOV_SPEED;
	if (mlx->game->grid[(int)(py + dx * MOV_SPEED)][(int)(px)] == '0')
		mlx->player->pos.y += dx * MOV_SPEED;
}
