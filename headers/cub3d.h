#ifndef CUB3D_H
# define CUB3D_H
# include "../mlx/mlx.h"
# include "../Libft/Libft/libft.h"
# include "../Libft/Libft/get_next_line.h"
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# define HEIGHT 1080
# define WIDTH 1920
# define MINIMAP_GRID 15
# define FOV 60
# define ROT_SPEED 0.1112
# define MOV_SPEED 0.2

typedef struct s_2dVector
{
	double	x;
	double	y;
}	t_v;


typedef struct s_2dintVector
{
	int	x;
	int	y;
}	t_i;

typedef struct s_rayVals
{
	t_v	rayDir;
	t_v	map;
	t_v	side;
	t_v	step;
	t_v	delta;
	t_v	wall;
}				t_rayVals;

/*
	Image Controller
*/
typedef struct s_imgController
{
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		nd;
}	t_img;

typedef struct s_player
{
	t_v			pos;
	t_v			dir;
	t_v			plane;
	t_rayVals	*d;
}	t_player;

typedef struct s_game
{
	char**	grid;
	int		row;
	char*	tex_paths[4];
	t_img	*textures;
	t_i		*image_sizes;
	t_i		tex;
	int		ceiling;
	int		floor;
}	t_game;

typedef struct s_mlxController
{
	void		*mlx;
	void		*window;
	t_img		*image;
	t_player	*player;
	t_game		*game;
}				t_mlx;

typedef struct s_draw_wall
{
	int	tex_x;
	int	wall_mx;
	int	wall_mn;
	int	l_h;
	int	t_h;
	int	t_w;
}				t_draw_wall;

void	process_args(t_game *game, char *path, t_player *player, t_mlx *mlx);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
void	draw_square(t_img *img, double x, double y, int colour);
void	draw_minimap(t_img *img, t_game *game, t_player *player, t_mlx *mlx);
void	draw_map(t_mlx *mlx);

int		get_trgb(int t, int r, int g, int b);
int		strToColour(char *str);
int		keyhandler(int keycode, t_mlx *mlx);
int		close_exit(t_mlx *vars);
double	map(double value, double from_high, double to_low, double to_high);
int		norm(double x, double y);
void	vert_line(int x, t_img *img, t_img *tex, t_draw_wall w);
void	diagonal_line(t_v start, t_v end, t_img *img);

#endif // !CUB3D_H
