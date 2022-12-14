#include "../headers/cub3d.h"

void	calc_rotation(t_player *player, char sign)
{
	double	oldDirX;
	double	oldPlaneX;
	double	rotation_speed;

	rotation_speed = -ROT_SPEED;
	if (sign == 'l')
		rotation_speed = ROT_SPEED;
	oldDirX = player->dir.x;
	oldPlaneX = player->plane.x;
	player->dir.x = oldDirX * cosf(rotation_speed) - player->dir.y * sinf(rotation_speed);
	player->dir.y = oldDirX * sinf(rotation_speed) + player->dir.y * cosf(rotation_speed);
	player->plane.x = oldPlaneX * cosf(rotation_speed) - player->plane.y * sinf(rotation_speed);
	player->plane.y = oldPlaneX * sinf(rotation_speed) + player->plane.y * cosf(rotation_speed);
}

void	calc_movement_f(t_mlx *mlx)
{
	double	posx;
	double	posy;
	double	dirx;
	double	diry;

	posx = mlx->player->pos.x;
	posy = mlx->player->pos.y;
	dirx = mlx->player->dir.x;
	diry = mlx->player->dir.y;
	if (mlx->game->grid[(int)(posy)][(int)(posx + dirx * MOV_SPEED)] == '0')
		mlx->player->pos.x += dirx * MOV_SPEED;
	if (mlx->game->grid[(int)(posy - diry * MOV_SPEED)][(int)(posx)] == '0')
		mlx->player->pos.y -= diry * MOV_SPEED;
}

void	calc_movement_b(t_mlx *mlx)
{
	double	posx;
	double	posy;
	double	dirx;
	double	diry;

	posx = mlx->player->pos.x;
	posy = mlx->player->pos.y;
	dirx = mlx->player->dir.x;
	diry = mlx->player->dir.y;
	if (mlx->game->grid[(int)(posy)][(int)(posx - dirx * MOV_SPEED)] == '0')
		mlx->player->pos.x -= dirx * MOV_SPEED;
	if (mlx->game->grid[(int)(posy + diry * MOV_SPEED)][(int)(posx)] == '0')
		mlx->player->pos.y += diry * MOV_SPEED;
}

int	keyhandler(int keycode, t_mlx *mlx)
{
	// Hareket olması için engel kontrolünü sağlayan koşullar eklendi (floating hareketlerde duvarlar bug da kalıyor)
	if (keycode == 53)
		exit(0);
	if (keycode == 0)
		calc_rotation(mlx->player, 'l');
	else if (keycode == 2)
		calc_rotation(mlx->player, 0);
	else if (keycode == 1)
		calc_movement_b(mlx);
	else if (keycode == 13)
		calc_movement_f(mlx);
	mlx_clear_window(mlx->mlx, mlx->window);
	draw_map(mlx);
	return (0);
}
