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
# define ROT_SPEED 0.1
# define MOV_SPEED 0.2

/*
	Psuedo vector struct
	@param	x
	@param	y
*/
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
	//Ray direction
	t_v	rayDir;
	//Int version of player pos
	t_v	map;
	//Side Dist
	t_v	side;
	//Which way to go
	t_v	step;
	//Initial Delta Distance
	t_v	delta;
	//Wall Dist and Side info
	t_v	wall;
}				t_rayVals;

/*
	Image Controller
*/
typedef struct s_imgController
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
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

/*
	Mlx and window pointer controller
	@param Mlx mlx pointer
	@param Window window pointer
*/
typedef struct s_mlxController
{
	void		*mlx;
	void		*window;
	t_img		*image;
	t_player	*player;
	t_game		*game;
}				t_mlx;


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
void	vert_line(int x, int line_start, int line_end, t_img *img, int texX, int tH, int lH, t_img *tex);
void	diagonal_line(t_v start, t_v end, t_img *img);

#endif // !CUB3D_H
