#include "../headers/cub3d.h"

int	char_to_index(char c, t_player *player)
{
	player->dir.x = 0;
	player->dir.y = 0;
	player->plane.x = 0;
	player->plane.y = 0;
	if (c == 'N' || c == 'E')
		return (1);
	else if (c == 'S' || c == 'W')
		return (-1);
	return (0);
}

char	*ft_strpbrk(char *string, char *set)
{
	int	i;

	while (*string)
	{
		i = 0;
		while (set[i])
		{
			if (*string == set[i])
				return string;
			i++;
		}
		string++;
	}
	return (NULL);
}

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

	textures = game->textures;
	tex_paths = game->tex_paths;
	size = game->image_sizes;
	textures[0].img = mlx_xpm_file_to_image(mlx->mlx, tex_paths[0], (int *)&size[0].x, (int *)&size[0].y);
	textures[1].img = mlx_xpm_file_to_image(mlx->mlx, tex_paths[1], (int *)&size[1].x, (int *)&size[1].y);
	textures[2].img = mlx_xpm_file_to_image(mlx->mlx, tex_paths[2], (int *)&size[2].x, (int *)&size[2].y);
	textures[3].img = mlx_xpm_file_to_image(mlx->mlx, tex_paths[3], (int *)&size[3].x, (int *)&size[3].y);
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
	i++;
	game->row = i;
	free(line);
}

void	process_args(t_game *game, char *path, t_player *player, t_mlx *mlx)
{
	int		fd;
	char	*ptr;
	char	*line;

	if ((fd = open(path, O_RDONLY)))
	{
		while ((line = get_next_line(fd)))
		{
			if (!process_tex(game, line))
				break ;
		}
		game->grid = malloc(sizeof(char * ) * 100);
		while (line)
		{
			process_grid(game, player, line);
			line = get_next_line(fd);
		}
		//Work in progress convert paths to images
		game->textures = malloc(sizeof(t_img) * 5);
		paths_to_img(mlx, game);
		// (void)mlx;
		player->d = malloc(sizeof(t_rayVals));
	}
	else
	{
		perror ("Couldn't find the file named ");
		perror (path);
		exit(2);
	}
}
