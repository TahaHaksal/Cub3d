#include "../headers/cub3d.h"

bool	process_tex(t_game *game, char *line)
{
	if (!ft_strncmp(line, "NO", 2))
		game->tex_paths[0] = ft_strtrim(&line[3], " \r\t\n");
	else if (!ft_strncmp(line, "SO", 2))
		game->tex_paths[1] = ft_strtrim(&line[3], " \r\t\n");
	else if (!ft_strncmp(line, "WE", 2))
		game->tex_paths[2] = ft_strtrim(&line[3], " \r\t\n");
	else if (!ft_strncmp(line, "EA", 2))
		game->tex_paths[3] = ft_strtrim(&line[3], " \r\t\n");
	else if (!ft_strncmp(line, "F", 1))
		game->floor = str_to_colour(&line[2]);
	else if (!ft_strncmp(line, "C", 1))
		game->ceiling = str_to_colour(&line[2]);
	else
	{
		return (false);
		free(line);
	}
	free(line);
	return (true);
}

// void	paths_to_img(t_mlx *mlx, t_game *game)
// {
// 	t_img	*textures;
// 	char	**tex_paths;
// 	t_i		*size;

// 	int (i) = -1;
// 	textures = game->textures;
// 	tex_paths = game->tex_paths;
// 	size = game->image_sizes;
// 	while (++i < 4)
// 		textures[i].img = mlx_xpm_file_to_image \
// 		(mlx->mlx, tex_paths[i], (int *)&size[i].x, (int *)&size[i].y);
// }

void	process_grid(t_game *game, t_player *player, char *line)
{
	static int	i;
	int			val;
	char		*ptr;

	game->grid[i] = ft_strdup(line);
	ptr = ft_strpbrk(game->grid[i], "NEWS");
	if (ptr)
	{
		val = char_to_index(*ptr, player);
		if (*ptr == 'N' || *ptr == 'S')
		{
			player->dir.y = val;
			player->plane.x = val;
		}
		else
		{
			player->dir.x = val;
			player->plane.y = -val;
		}
		*ptr = '0';
		player->pos.x = ft_strlen(line) - ft_strlen(ptr);
		player->pos.y = i;
	}
	game->row = ++i;
	free(line);
}

void	init_game(t_game *game, t_mlx *mlx, t_img *textures)
{
	int	a;
	int	x,y;
	t_i		*size;
	char	**tex_paths;

	tex_paths = game->tex_paths;
	size = game->image_sizes;
	textures[0].img = mlx_xpm_file_to_image(mlx->mlx, tex_paths[0], &size[0].x, &size[0].y);
	textures[1].img = mlx_xpm_file_to_image(mlx->mlx, tex_paths[1], &size[1].x, &size[1].y);
	textures[2].img = mlx_xpm_file_to_image(mlx->mlx, tex_paths[2], &size[2].x, &size[2].y);
	textures[3].img = mlx_xpm_file_to_image(mlx->mlx, tex_paths[3], &size[3].x, &size[3].y);
	printf("%p\n", textures[0].img);
	textures[0].addr = mlx_get_data_addr(textures[0].img, &(textures[0].bits_per_pixel),  &textures[0].line_length,  &textures[0].endian);
	textures[1].addr = mlx_get_data_addr(textures[1].img, &(textures[1].bits_per_pixel),  &(textures[1].line_length),  &(textures[1].endian));
	textures[2].addr = mlx_get_data_addr(textures[2].img, &(textures[2].bits_per_pixel),  &(textures[2].line_length),  &(textures[2].endian));
	textures[3].addr = mlx_get_data_addr(textures[3].img, &(textures[3].bits_per_pixel),  &(textures[3].line_length),  &(textures[3].endian));
	printf("%p\n", textures[0].addr);

	game->weapon = mlx_xpm_file_to_image(mlx->mlx, \
					"/Users/dkarhan/Desktop/ak-47.xpm", &a, &a);
	game->miniMap = 1;
	game->cursor = 1;
	game->mouse_first = 0;
	game->mouse_last = 0;
	// paths_to_img(mlx, game);
}

void	process_args(t_game *game, char *path, t_player *player, t_mlx *mlx)
{
	int		fd;
	char	*ptr;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd > 2)
	{
		line = get_next_line(fd);
		while (line)
		{
			if (!process_tex(game, line))
				break ;
			line = get_next_line(fd);
		}
		game->grid = malloc(sizeof(char *) * 100);
		while (line)
		{
			process_grid(game, player, line);
			line = get_next_line(fd);
		}
		game->image_sizes = malloc(sizeof(t_i) * 5);
		game->textures = malloc(sizeof(t_img) * 5);
		player->d = malloc(sizeof(t_rayVals));
		init_game(game, mlx, game->textures);
	}
	else
		error ("Error: Couldn't find the file!\n");
}
