#include "../headers/cub3d.h"

// void	vert_line(int x, int line_start, int line_end, t_img *img, int color)
// {
// 	while (line_start++ < line_end)
// 		my_mlx_pixel_put(img, x, line_start, color);
// }

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
		test = tex->addr + ((texY % 64) * tex->line_length + texX * (tex->bits_per_pixel / 8));
		color = *(unsigned int *)test;
		my_mlx_pixel_put(img, x, line_start, color);
		texPos += step;
	}
}

void	diagonal_line(t_v start, t_v end, t_img *img, t_mlx *mlx)
{
	double	dx;
	double	dy;
	double	Xinc;
	double	Yinc;
	int		steps;
	int (i) = -1;

	Xinc = dx / (float) steps;
	Yinc = dy / (float) steps;
	dx = end.x - start.x;
	dy = end.y - start.y;
	steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
	while (++i < 125)
	{
		if (mlx->game->grid[((int)(start.y) / MINIMAP_GRID)][((int)(start.x) / MINIMAP_GRID)] != '1')
		{
			my_mlx_pixel_put(img, (int)roundf(start.x), (int)roundf(start.y), get_trgb(i * 2, 0, 0, 255));
			start.x += Xinc;
			start.y += Yinc;
		}
		else
			break;
	}
}
