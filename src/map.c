#include "../headers/cub3d.h"

int	norm(double x, double y)
{
	return (abs((int)pow(x, 2) + (int)pow(y,2)));
}

double	map(double value, double from_high, double to_low, double to_high)
{
	double	a;
	double	b;

	a = to_high - to_low;
	b = from_high;
	return (to_low + (a * (value / b)));
}
