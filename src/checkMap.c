#include "../headers/cub3d.h"

int	map_control2(char **m, char *line, int *j, int *len)
{
	static int	temp;
	int			player_count;

	int (i) = -1;
	player_count = 0;
	if (++temp <= 6)
		return (0);
	m[++(*j)] = ft_strdup(line);
	i = -1;
	while (m[*j][++i])
	{
		if (!ft_strchr(" 01NEWS", m[*j][i]) && m[*j][i] != '\n')
			error("Error : wrong map character!\n");
		else if (ft_strchr("NEWS", m[*j][i]))
			player_count += 1;
	}
	if ((*len) < ft_strlen(m[*j]))
		(*len) = ft_strlen(m[*j]);
	return (player_count);
}

char	**map_control(char *path, t_v *j_len, int j, int i)
{
	int		fd;
	char	*line;
	char	**m;

	int (len) = 0;
	int (player_count) = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		error("Error : wrong file!\n");
	m = malloc(sizeof(char *) * 300);
	line = get_next_line(fd);
	while (line)
	{
		player_count += map_control2(m, line, &j, &len);
		line = get_next_line(fd);
	}
	if (player_count != 1)
		error("Error : can only be 1 player!\n");
	close(fd);
	j_len->x = j;
	j_len->y = len;
	return (m);
}

void	top_bottom_check(char **m, int i, int j, int len)
{
	int	a;

	while (++i < len)
	{
		a = -1;
		while (m[++a])
		{
			if (i > ft_strlen(m[a]))
				break ;
			if (m[a][i] == ' ')
				continue ;
			else if (m[a][i] == '0')
				error("error: (topCheck) map error!\n");
			else
				break ;
		}
		a = j + 1;
		while (a-- >= 1)
		{
			if (m[a][i] == ' ')
				continue ;
			else if (m[a][i] == '0')
				error("error: (bottomCheck) map error!\n");
			else
				break ;
		}
	}
}

void	right_left_check(char **m, int i, int j, int len)
{
	int	a;

	while (++i < j)
	{
		a = ft_strlen(m[i]) - 1;
		while (a && m[i][--a])
		{
			if (m[i][a] == ' ')
				continue ;
			else if (m[i][a] == '0')
				error("error: (RightCheck) map error!\n");
			else
				break ;
		}
		a = -1;
		while (m[i][++a])
		{
			if (m[i][a] == ' ')
				continue ;
			else if (m[i][a] == '0')
				error("error: (LeftCheck) map error!\n");
			else
				break ;
		}
	}
}

void	character_check(char **m, int i, int j)
{
	int	a;

	while (++i < j)
	{
		a = -1;
		while (m[i][++a])
		{
			if (m[i][a] == ' ')
			{
				if ((i != 0 && (m[i - 1][a] == '0')) ||
					(i != j - 1 && m[i + 1][a] == '0') ||
					(a != 0 && m[i][a - 1] == '0') ||
					(a != ft_strlen(m[i]) - 1) && m[i][a + 1] == '0')
					error("error: (SpaceCheck) map error!\n");
			}
			else if (ft_strchr("0NEWS", m[i][a]))
				if ((i != 0) && (a >= ft_strlen(m[i - 1]) - 1)
					|| (i != ft_strlen(m[i]) && a >= ft_strlen(m[i + 1]) - 1)
					|| (i != j - 1 && m[i + 1][a] == ' ')
					|| (a != 0 && m[i][a - 1] == ' ')
					|| ((a != ft_strlen(m[i]) - 1) && m[i][a + 1] == ' '))
				{
					printf("%d %d\n", a, i);
					error("error: (Zero-PlayerCheck) map error!\n");
				}
		}
	}
}
