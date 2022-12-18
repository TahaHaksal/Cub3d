#include "../headers/cub3d.h"

int	keyhandler(int keycode, t_mlx *mlx)
{
	// Hareket olması için engel kontrolünü sağlayan koşullar eklendi (floating hareketlerde duvarlar bug da kalıyor)
	if (keycode == 53)
		exit(0);
	if (keycode == 0)
		{if (mlx->game.grid[(int)(mlx->player.y)][(int)(mlx->player.x - 1)] == '0')
			mlx->player.x -= 1;}
	else if (keycode == 2)
		{if (mlx->game.grid[(int)(mlx->player.y)][(int)(mlx->player.x + 1)] == '0')
			mlx->player.x += 1;}
	else if (keycode == 1)
		{if (mlx->game.grid[(int)(mlx->player.y + 1)][(int)(mlx->player.x)] == '0')
			mlx->player.y += 1;}
	else if (keycode == 13)
		{if (mlx->game.grid[(int)(mlx->player.y - 1)][(int)(mlx->player.x)] == '0')
			mlx->player.y -= 1;}
	draw_minimap(&mlx->image, &mlx->game, &mlx->player, mlx);
	return (0);
}
