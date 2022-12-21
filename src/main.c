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
	process_args(&game, av[1], &player);
	mlx.mlx = mlx_init();
	mlx.window = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "Cub3D");
	image.img = mlx_new_image(mlx.mlx, WIDTH, HEIGHT);
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel, &image.line_length, &image.endian);

	//SegFault engellemek için
	mlx.image = &image;
	mlx.game = &game;
	mlx.player = &player;

	draw_map(&mlx); // Tavan ve zemini ekrana bastırıyor
	// draw_minimap(mlx.image, mlx.game, mlx.player, &mlx);

	mlx_hook(mlx.window, 2, 1L << 0, keyhandler, &mlx); // player hareketi -------> burada &mlx.player yolladığımız için x y 0 geliyordu.
	mlx_hook(mlx.window, 17, 0, close_exit, &mlx); // esc

	mlx_loop(mlx.mlx);
	// mlx_destroy_image(mlx.mlx, mlx.image->img);
	// mlx_destroy_window(mlx.mlx, mlx.window);
	exit(0);
}
