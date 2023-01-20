/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarhan <dkarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 08:54:48 by mhaksal           #+#    #+#             */
/*   Updated: 2023/01/20 11:57:09 by dkarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

int	keyhandler(int keycode, t_mlx *mlx)
{
	if (keycode == 53)
		exit(0);
	else if (keycode == 123)
		calc_rotation(mlx->player, 'l');
	else if (keycode == 124)
		calc_rotation(mlx->player, 0);
	else if (keycode == 0)
		calc_movement_l(mlx);
	else if (keycode == 2)
		calc_movement_r(mlx);
	else if (keycode == 1)
		calc_movement_b(mlx);
	else if (keycode == 13)
		calc_movement_f(mlx);
	else if (keycode == 46)
		mlx->game->mini_map += 1;
	else if (keycode == 14)
		mlx->game->cursor += 1;
	return (0);
}

int	mouse_move(int x, int y, t_mlx *mlx)
{
	mlx->game->mouse_last = x;
	if (mlx->game->cursor % 2)
		mlx_mouse_hide();
	else
		mlx_mouse_show();
	if (mlx->game->mouse_first != mlx->game->mouse_last)
	{
		if (mlx->game->mouse_first > mlx->game->mouse_last)
			calc_rotation(mlx->player, 'l');
		else
			calc_rotation(mlx->player, 0);
		if (mlx->game->mouse_last > WIDTH)
			mlx_mouse_move(mlx->window, 0, HEIGHT / 2);
		if (mlx->game->mouse_last <= 0)
			mlx_mouse_move(mlx->window, WIDTH, HEIGHT / 2);
		mlx->game->mouse_first = mlx->game->mouse_last;
	}
	return (0);
}
