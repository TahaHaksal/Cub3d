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
		game->floor = strToColour(&line[2]);
	else if (!ft_strncmp(line, "C", 1))
		game->ceiling = strToColour(&line[2]);
	else
	{
		return (false);
		free(line);
	}
	free(line);
	return (true);
}

void	paths_to_img(t_mlx *mlx, t_game *game)
{
	t_img	*textures;
	char	**tex_paths;
	t_v		*size;

	int (i) = -1;
	textures = game->textures;
	tex_paths = game->tex_paths;
	size = game->image_sizes;
	while (++i < 4)
		textures[i].img = mlx_xpm_file_to_image \
		(mlx->mlx, tex_paths[i], (int *)&size[i].x, (int *)&size[i].y);
}

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

void	init_game(t_game *game, t_mlx *mlx)
{
	int	a;

	game->weapon = mlx_xpm_file_to_image(mlx->mlx, \
					"/Users/dkarhan/Desktop/ak-47.xpm", &a, &a);
	game->miniMap = 1;
	game->cursor = 1;
	game->mouse_first = 0;
	game->mouse_last = 0;
	game->grid = malloc(sizeof(char *) * 100);
	game->textures = malloc(sizeof(t_img) * 5);
	paths_to_img(mlx, game);
}

void	process_args(t_game *game, char *path, t_player *player, t_mlx *mlx)
{
	int		fd;
	char	*ptr;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd > 2)
	{
		init_game(game, mlx);
		line = get_next_line(fd);
		while (line)
		{
			if (!process_tex(game, line))
				break ;
			line = get_next_line(fd);
		}
		while (line)
		{
			process_grid(game, player, line);
			line = get_next_line(fd);
		}
		player->d = malloc(sizeof(t_rayVals));
	}
	else
		error ("Error: Couldn't find the file!\n");
}
