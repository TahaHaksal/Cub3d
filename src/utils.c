#include "../headers/cub3d.h"

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
