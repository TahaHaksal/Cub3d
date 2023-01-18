#include "../headers/cub3d.h"

/*
	@param x ekranın hangi sütunu çizilecek
	@param img tüm ekran image'ı
	@param tex texture image'ı
	@param w header'dan bak :D
*/
void	vert_line(int x, t_img *img, t_img *tex, t_draw_wall w)
{
	double	step;
	double	tex_pos;
	int		tex_y;
	char	*test;

	step = 1.0 * w.t_h / w.l_h;
	tex_pos = (w.wall_mn - HEIGHT / 2 + w.l_h / 2) * step;
	while (w.wall_mn < w.wall_mx)
	{
		tex_y = (int)tex_pos;
		test = tex->addr + ((tex_y % w.t_w) * tex->ll + w.tex_x * (tex->bpp / 8));
		my_mlx_pixel_put(img, x, w.wall_mn, *(unsigned int *)test);
		tex_pos += step;
		w.wall_mn++;
	}
}

void	diagonal_line(t_v start, t_v end, t_img *img)
{
	double	dx;
	double	dy;
	double	inc_x;
	double	inc_y;
	int		steps;

	inc_x = dx / (float) steps;
	inc_y = dy / (float) steps;
	dx = end.x - start.x;
	dy = end.y - start.y;
	steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
	for (int i = 0; i <= steps; i++)
	{
		my_mlx_pixel_put(img, (int)roundf(start.x), (int)roundf(start.y), 0x000000FF);
		start.x += inc_x;
		start.y += inc_y;
	}
}
