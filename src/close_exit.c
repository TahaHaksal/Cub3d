#include "../headers/cub3d.h"

int	close_exit(t_mlx *vars)
{
	printf("Game Over!\n");
	if (vars)
		mlx_destroy_window(vars->mlx, vars->window);
	exit(0);
}