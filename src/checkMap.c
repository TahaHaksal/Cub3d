#include "../headers/cub3d.h"

int	topCheck(char **M, int i, int j, int len)
{
	while (++i < len)
	{
		int a = -1;
		while (M[++a])
		{
			if (M[a][i] == ' ')
				continue;
			else if (M[a][i] == '0')
				return (0);
			else
				break;
		}
	}
	return (1);
}

int	bottomCheck(char **M, int i, int j, int len)
{
	int	num;

	while (++i < len)
	{
		int a = -1;
		while (M[++a])
		{
			if (M[a][i] == ' ')
				continue;
			else if (M[a][i] == '0' || M[a][i] == 'N' || M[a][i] == 'E' ||
					M[a][i] == 'W' || M[a][i] == 'S')
				num = 0;
			else
				num = 1;
		}
		if (num == 0)
			return (0);
	}
	return (1);
}

int	RightAndLeftCheck(char **M, int i, int j, int len)
{
	int	num;
	int	a;

	while (++i < j)
	{
		a = ft_strlen(M[i]) - 1;
		while (M[i][--a])
		{
			if (M[i][a] == ' ')
				continue;
			else if (M[i][a] == '0')
				return (0);
			else
				break;
		}
		a = -1;
		while (M[i][++a])
		{
			if (M[i][a] == ' ')
				continue;
			else if (M[i][a] == '0')
				return (0);
			else
				break;
		}
	}
	return (1);
}

int	SpaceAndZeroCheck(char **M, int i, int j)
{
	while (++i < j)
	{
		int	a = -1;
		while (M[i][++a])
		{
			if (M[i][a] == ' ')
			{
				if((i != 0 && (M[i - 1][a] == '0')))
					return (0);
				else if (i != j - 1 && M[i + 1][a] == '0')
					return (0);
				else if (a != 0 && M[i][a - 1] == '0')
					return (0);
				else if ((a != ft_strlen(M[i]) - 1) && M[i][a + 1] == '0')
					return (0);
			}
			else if (ft_strchr("0NEWS", M[i][a]))
			{
				if (i != 0 && a > ft_strlen(M[i - 1])) // Yukarısı none ise
					return (0);
				else if (i != ft_strlen(M[i]) && a > ft_strlen(M[i + 1])) // Aşağısı none ise
					return (0);
				else if (i != j - 1 && M[i + 1][a] == ' ')
					return (0);
				else if (a != 0 && M[i][a - 1] == ' ')
					return (0);
				else if ((a != ft_strlen(M[i]) - 1) && M[i][a + 1] == ' ')
					return (0);
			}
		}
	}
	return (1);
}

int checkMap(char *path)
{
    int fd, j = -1, i = 0, len = 0, player_count = 0;
    char *line;
	char **M = malloc(sizeof(char *) * 100);

    fd = open(path, O_RDONLY);
    while ((line = get_next_line(fd)))
    {
		// Map gelene kadar ilerle Map gelince çift boyutlu matrise haritayı ekle.
		if (++i <= 6)
			continue ;
		M[++j] = ft_strdup(line);
		if (ft_strnstr(M[j], "N", ft_strlen(M[j])) ||
			ft_strnstr(M[j], "E", ft_strlen(M[j])) ||
			ft_strnstr(M[j], "W", ft_strlen(M[j])) ||
			ft_strnstr(M[j], "S", ft_strlen(M[j])))
			player_count += 1;
		if (len < ft_strlen(M[j]))
			len = ft_strlen(M[j]);
    }
	if (player_count != 1)
		return (0);
	M[j + 1] = NULL;
	// Map'e üstten alttan sağdan soldan boşlukları atlayıp bakınca 1 gelmezse ya da
	// ' ' ile '0' 4 eksenden temas halindeyse error patlatıyor.
	if (!topCheck(M, -1, j, len) || !bottomCheck(M, -1, j, len) ||
		!RightAndLeftCheck(M, -1, j, len) ||
		!SpaceAndZeroCheck(M, -1, j))
		return (0);
    return (1);
}
