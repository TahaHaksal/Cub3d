#include "../headers/cub3d.h"

void	vert_line(int x, t_i wall, t_img *img, int texX, t_i h, t_img *tex)
{
	double	step;
	double	texPos;
	int		texY;
	char	*test;

	step = 1.0 * h.x / h.y;
	texPos = (wall.x - HEIGHT / 2 + h.y / 2) * step;
	while (wall.x++ < wall.y)
	{
		texY = texPos;
		test = tex->addr + ((texY % 64) * tex->ll + texX * (tex->bpp / 8));
		my_mlx_pixel_put(img, x, wall.x, *(unsigned int *)test);
		texPos += step;
	}
}

void	diagonal_line(t_v start, t_v end, t_img *img)
{
	double	dx;
	double	dy;
	int		steps;
	double	Xinc;
	double	Yinc;

	Xinc = dx / (float) steps;
	Yinc = dy / (float) steps;
	dx = end.x - start.x;
	dy = end.y - start.y;
	steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
	for (int i = 0; i <= steps; i++)
	{
		my_mlx_pixel_put(img, (int)roundf(start.x), (int)roundf(start.y), 0x000000FF);
		start.x += Xinc;
		start.y += Yinc;
	}
}
