/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccess_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarhan <dkarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 08:55:00 by mhaksal           #+#    #+#             */
/*   Updated: 2023/01/20 11:49:55 by dkarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	else if (ft_strpbrk(line, "01"))
		return (false);
	free(line);
	return (true);
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

void	init_game(t_game *game, t_mlx *mlx, t_img *textrs)
{
	int		x;
	int		y;
	t_i		*size;
	char	**tex_paths;

	tex_paths = game->tex_paths;
	size = game->image_sizes;
	int (i) = -1;
	while (++i <= 3)
	{
		textrs[i].img = mlx_xpm_file_to_image(mlx->mlx, \
			tex_paths[i], &size[i].x, &size[i].y);
		if (!textrs[i].img)
			error("Couldn't find the image file\n");
		textrs[i].addr = mlx_get_data_addr(textrs[i].img, \
		&(textrs[i].bpp), &textrs[i].ll, &textrs[i].nd);
	}
	game->weapon = mlx_xpm_file_to_image(mlx->mlx, \
		"./images/ak-47.xpm", &i, &i);
	game->mini_map = 1;
	game->cursor = 1;
	game->mouse_first = 0;
	game->mouse_last = 0;
}

void	process_args(t_game *game, char *path, t_player *player, t_mlx *mlx)
{
	int		fd;
	char	*ptr;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd <= 2)
		error ("Error: Couldn't find the file!\n");
	line = get_next_line(fd);
	while (line)
	{
		if (!process_tex(game, line))
			break ;
		line = get_next_line(fd);
	}
	game->grid = malloc(sizeof(char *) * 1024);
	while (line)
	{
		process_grid(game, player, line);
		line = get_next_line(fd);
	}
	close(fd);
	game->image_sizes = malloc(sizeof(t_i) * 5);
	game->textures = malloc(sizeof(t_img) * 5);
	player->d = malloc(sizeof(t_rayVals));
	init_game(game, mlx, game->textures);
}
