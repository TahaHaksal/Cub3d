#include "../headers/cub3d.h"

void	vert_line(int x, int line_start, int line_end, t_img *img, int texX, int tH, int lH, t_img *tex)
{
	double			step;
	double			texPos;
	int				texY;
	char			*test;
	unsigned int	color;

	step = 1.0 * tH / lH;
	texPos = (line_start - HEIGHT / 2 + lH / 2) * step;
	while (line_start++ < line_end)
	{
		texY = (int)texPos & (tH - 1);
		test = tex->addr + ((texY % 32) * tex->line_length + texX * (tex->bits_per_pixel / 8));
		color = *(unsigned int *)test;
		my_mlx_pixel_put(img, x, line_start, color);
		texPos += step;
	}
}


// dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
// 	*(unsigned int *)dst = color;
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
