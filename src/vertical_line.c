#include "../headers/cub3d.h"

void	vert_line(int x, int line_start, int line_end, t_img *img)
{
	while (line_start++ < line_end)
		my_mlx_pixel_put(img, x, line_start, 0x005050FF);
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
