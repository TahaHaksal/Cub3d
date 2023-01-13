#include "../headers/cub3d.h"


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

int	main(int ac, char **av)
{
	t_mlx		mlx;
	t_img		image;
	t_game		game;
	t_player	player;

	if (ac != 2 || !checkMap(av[1]))
	{
		perror("Maps Error or This program needs 2 arguments to function!");
		exit(1);
	}
	mlx.mlx = mlx_init();
	process_args(&game, av[1], &player, &mlx);
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
	// mlx_destroy_image(mlx.mlx, mlx.image->img);
	// mlx_destroy_window(mlx.mlx, mlx.window);
	exit(0);
}
