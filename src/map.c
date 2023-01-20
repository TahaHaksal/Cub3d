/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaksal <mhaksal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 08:54:57 by mhaksal           #+#    #+#             */
/*   Updated: 2023/01/20 08:54:58 by mhaksal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

int	norm(double x, double y)
{
	return (abs((int)pow(x, 2) + (int)pow(y, 2)));
}

double	map(double value, double from_high, double to_low, double to_high)
{
	return (to_low + ((to_high - to_low) * (value / (from_high))));
}
