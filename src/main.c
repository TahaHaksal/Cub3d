#include "../headers/cub3d.h"

int	get_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	strToColour(char *str)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(str);
	while (ft_isdigit(*str))
		str++;
	str++;
	g = ft_atoi(str);
	while (ft_isdigit(*str))
		str++;
	str++;
	b = ft_atoi(str);
	return (get_trgb(0, r, g, b));
}

void	process_args(t_game *game, char *path, t_player *player)
{
	int		fd;
	char	*ptr;
	char	*line;
	int		i;

	if ((fd = open(path, O_RDONLY)))
	{
		while ((line = get_next_line(fd)))
		{
			if (!ft_strncmp(line, "NO", 2))
				game->n_tex = ft_strdup(ft_strtrim(&line[3], " \r\t"));
			else if (!ft_strncmp(line, "SO", 2))
				game->s_tex = ft_strdup(ft_strtrim(&line[3], " \r\t"));
			else if (!ft_strncmp(line, "WE", 2))
				game->w_tex = ft_strdup(ft_strtrim(&line[3], " \r\t"));
			else if (!ft_strncmp(line, "EA", 2))
				game->e_tex = ft_strdup(ft_strtrim(&line[3], " \r\t"));
			else if (!ft_strncmp(line, "F", 1))
				game->floor = strToColour(ft_strtrim(&line[2], " \r\t"));
			else if (!ft_strncmp(line, "C", 1))
				game->ceiling = strToColour(ft_strtrim(&line[2], " \r\t"));
			else
				break ;
			free(line);
		}
		i = 0;
		game->grid = malloc(sizeof(char * ) * 100);
		while (line)
		{
			game->grid[i] = ft_strdup(line);
			if ((ptr = ft_strchr(game->grid[i], 'N')))
			{
				*ptr = '0';
				player->x = ft_strlen(line) - ft_strlen(ptr);
				player->y = i;
			}
			i++;
			free(line);
			line = get_next_line(fd);
		}
	}
	else
	{
		perror ("Couldn't find the file named ");
		perror (path);
		exit(2);
	}
}

void	draw_square(t_img *img, int x, int y, int colour)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP_GRID)
	{
		j = 0;
		while (j < MINIMAP_GRID)
		{
			my_mlx_pixel_put(img, (MINIMAP_GRID * x) + i, (MINIMAP_GRID * y) + j, colour);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_img *img, t_game *game, t_player *player)
{
	for (int i = 0; game->grid[i]; i++)
	{
		for (int j = 0; game->grid[i][j]; j++)
		{
			if (game->grid[i][j] == '1')
				draw_square(img, j, i, get_trgb(0, 255, 0, 0));
			else if (game->grid[i][j] == '0')
				draw_square(img, j, i, 0x00FFFFFF);
		}
	}
	draw_square(img, player->x, player->y, 0x0000FF00);
}

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
	draw_minimap(&image, &game, &player);
	mlx_put_image_to_window(mlx.mlx, mlx.window, image.img, 0, 0);
	mlx_loop(mlx.mlx);
	mlx_destroy_image(mlx.mlx, image.img);
	mlx_destroy_window(mlx.mlx, mlx.window);
	exit(0);
}
