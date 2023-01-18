#include "../headers/cub3d.h"

int	main(int ac, char **av)
{
	t_mlx		mlx;
	t_img		image;
	t_game		game;
	t_player	player;

	if (ac != 2)
	{
		perror("This program needs 2 arguments to function!");
		exit(1);
	}
	mlx.mlx = mlx_init();
	game.grid = malloc(sizeof(char *) * 200);
	process_args(&game, av[1], &player, &mlx);
	mlx.window = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "Cub3D");
	image.img = mlx_new_image(mlx.mlx, WIDTH, HEIGHT);
	image.addr = mlx_get_data_addr(image.img, &image.bpp, &image.ll, &image.nd);
	mlx.image = &image;
	mlx.game = &game;
	mlx.player = &player;
	draw_map(&mlx);
	mlx_hook(mlx.window, 2, 1L << 0, keyhandler, &mlx);
	mlx_hook(mlx.window, 17, 0, close_exit, &mlx);
	mlx_loop(mlx.mlx);
	exit(0);
}
