#include "../headers/cub3d.h"

int	get_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	str_to_colour(char *str)
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
