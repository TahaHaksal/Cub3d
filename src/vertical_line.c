#include "../headers/cub3d.h"

void	vert_line(int x, t_img *img, t_img *tex, t_draw_wall w)
{
	double	step;
	double	tex_pos;
	int		tex_y;
	char	*test;

	int (t) = ((HEIGHT / w.l_h) * 20);
	if (t > 255)
		t = 255;
	step = 1.0 * w.t_h / w.l_h;
	tex_pos = (w.wall_mn - HEIGHT / 2 + w.l_h / 2) * step;
	while (w.wall_mn < w.wall_mx)
	{
		tex_y = (int)tex_pos;
		test = tex->addr + ((tex_y % w.t_w) * \
		tex->ll + w.tex_x * (tex->bpp / 8));
		my_mlx_pixel_put(img, x, w.wall_mn, *(unsigned int *)test + (t << 24));
		tex_pos += step;
		w.wall_mn++;
	}
}

void	diagonal_line(t_v start, t_v end, t_img *img, t_mlx *mlx)
{
	double (dx) = end.x - start.x;
	double (dy) = end.y - start.y;
	int (steps) = fabs(dy);
	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
	double (Xinc) = dx / (float) steps;
	double (Yinc) = dy / (float) steps;
	int (i) = -1;
	int (m) = MINIMAP_GRID;
	while (++i < 125)
	{
		if (mlx->game->grid[((int)(start.y) / m)][((int)(start.x) / m)] != '1')
		{
			my_mlx_pixel_put(img, (int)roundf(start.x), \
			(int)roundf(start.y), get_trgb(i * 2, 0, 0, 255));
			start.x += Xinc;
			start.y += Yinc;
		}
		else
			break ;
	}
}
