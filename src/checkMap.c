#include "../headers/cub3d.h"

void	error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}

char	**MapControl(char *path, t_v *j_len, int j, int i)
{
    int (len) = 0;
    int (player_count) = 0;
	int		fd;
	char	*line;
	char	**M;

    fd = open(path, O_RDONLY);
	if (fd < 0)
		error("Error : wrong file!\n");
	M = malloc(sizeof(char *) * 100);
    while ((line = get_next_line(fd)))
    {
		if (++i <= 6) // Map gelene kadar ilerle Map gelince çift boyutlu matrise haritayı ekle.
			continue ;
		M[++j] = ft_strdup(line);
		i = -1;
		while (M[j][++i])
		{
			if (!ft_strchr(" 01NEWS", M[j][i]) && M[j][i] != '\n')
				error("Error : wrong map character!\n");
			else if (ft_strchr("NEWS", M[j][i]))
				player_count += 1;
		}
		if (len < ft_strlen(M[j]))
			len = ft_strlen(M[j]); // Haritanın max genişliği
		i = 100;
    }
	if (player_count != 1)
		error("Error : can only be 1 player!\n");
	close(fd);
	j_len->x = j;
	j_len->y = len;
	return (M);
}

void	TopBottomCheck(char **M, int i, int j, int len)
{
	int	a;

	while (++i < len)
	{
		a = -1;
		while (M[++a])
		{
			if (M[a][i] == ' ')
				continue;
			else if (M[a][i] == '0')
				error("error: (topCheck) map error!\n");
			else
				break;
		}
		a = j + 1;
		while (a-- >= 1)
		{
			if (M[a][i] == ' ')
				continue;
			else if (M[a][i] == '0')
				error("error: (bottomCheck) map error!\n");
			else
				break;
		}
	}
}

void	RightLeftCheck(char **M, int i, int j, int len)
{
	int	a;

	while (++i < j)
	{
		a = ft_strlen(M[i]) - 1;
		while (a && M[i][--a])
		{
			if (M[i][a] == ' ')
				continue;
			else if (M[i][a] == '0')
				error("error: (RightCheck) map error!\n");
			else
				break;
		}
		a = -1;
		while (M[i][++a])
		{
			if (M[i][a] == ' ')
				continue;
			else if (M[i][a] == '0')
				error("error: (LeftCheck) map error!\n");
			else
				break;
		}
	}
}

void	CharacterCheck(char **M, int i, int j)
{
	int	a;

	while (++i < j)
	{
        a = -1;
		while (M[i][++a])
		{
			if (M[i][a] == ' ')
			{
				if( (i != 0 && (M[i - 1][a] == '0')) ||
					(i != j - 1 && M[i + 1][a] == '0') ||
					(a != 0 && M[i][a - 1] == '0') ||
					(a != ft_strlen(M[i]) - 1) && M[i][a + 1] == '0')
					error("error: (SpaceCheck) map error!\n");
			}
			else if (ft_strchr("0NEWS", M[i][a]))
			{
				if (i != 0 && a > ft_strlen(M[i - 1]) ||
					(i != ft_strlen(M[i]) && a > ft_strlen(M[i + 1])) ||
					(i != j - 1 && M[i + 1][a] == ' ') ||
					(a != 0 && M[i][a - 1] == ' ') ||
					((a != ft_strlen(M[i]) - 1) && M[i][a + 1] == ' '))
					error("error: (Zero-PlayerCheck) map error!\n");
			}
		}
	}
}
