#include "../headers/cub3d.h"

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
				game->n_tex = ft_strtrim(&line[3], " \r\t\n");
			else if (!ft_strncmp(line, "SO", 2))
				game->s_tex = ft_strtrim(&line[3], " \r\t\n");
			else if (!ft_strncmp(line, "WE", 2))
				game->w_tex = ft_strtrim(&line[3], " \r\t\n");
			else if (!ft_strncmp(line, "EA", 2))
				game->e_tex = ft_strtrim(&line[3], " \r\t\n");
			else if (!ft_strncmp(line, "F", 1))
				game->floor = strToColour(&line[2]);
			else if (!ft_strncmp(line, "C", 1))
				game->ceiling = strToColour(&line[2]);
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
				player->pos.x = ft_strlen(line) - ft_strlen(ptr);
				player->pos.y = i;
				player->dir.x = 0;
				player->dir.y = 1;
				player->plane.x = -1;
				player->plane.y = 0;
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
