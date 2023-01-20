/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaksal <mhaksal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 08:55:04 by mhaksal           #+#    #+#             */
/*   Updated: 2023/01/20 08:55:05 by mhaksal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	map_free(char **Map, int j)
{
	while (j >= 0)
		free(Map[j--]);
	free(Map);
}

void	error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}

int	close_exit(t_mlx *vars)
{
	printf("Game Over!\n");
	if (vars)
		mlx_destroy_window(vars->mlx, vars->window);
	exit(0);
}

char	*ft_strpbrk(char *string, char *set)
{
	int	i;

	while (*string)
	{
		i = -1;
		while (set[++i])
			if (*string == set[i])
				return (string);
		string++;
	}
	return (NULL);
}

int	char_to_index(char c, t_player *player)
{
	player->dir.x = 0;
	player->dir.y = 0;
	player->plane.x = 0;
	player->plane.y = 0;
	if (c == 'N' || c == 'E')
		return (1);
	else if (c == 'S' || c == 'W')
		return (-1);
	return (0);
}
