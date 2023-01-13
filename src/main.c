#include "../headers/cub3d.h"

void	freeMap(char **Map, int i)
{
	while (i--)
		free(Map[i]);
}

void checkMap(char *path)
{
	t_v	j_len;
	char **Map;

	Map = MapControl(path, &j_len, -1, 0);
	TopBottomCheck(Map, -1, (int)j_len.x, (int)j_len.y);
	RightLeftCheck(Map, -1, (int)j_len.x, (int)j_len.y);
	CharacterCheck(Map, -1, (int)j_len.x);
	freeMap(Map, 100);
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

void	start_game(char *av)
{
	t_mlx		mlx;
	t_img		image;
	t_game		game;
	t_player	player;

	mlx.mlx = mlx_init();
	process_args(&game, av, &player, &mlx);
	
	mlx.window = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "Cub3D");
	image.img = mlx_new_image(mlx.mlx, WIDTH, HEIGHT);
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel, &image.line_length, &image.endian);

	mlx.image = &image;
	mlx.game = &game;
	mlx.player = &player;

	mlx_hook(mlx.window, 2, 1L << 0, keyhandler, &mlx);
	mlx_hook(mlx.window, 17, 0, close_exit, &mlx);
	mlx_hook(mlx.window, 6, 0L, &mouse_move, &mlx);
	mlx_loop_hook(mlx.mlx, draw_map, &mlx);
	mlx_loop(mlx.mlx);
}

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		checkMap(av[1]);
		start_game(av[1]);
	}
	else
		error("Error: 2 arguments required for the game!\n");
	return (0);
}
