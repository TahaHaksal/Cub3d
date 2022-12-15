#ifndef CUB3D_H
# define CUB3D_H
# include "../mlx/mlx.h"
# include "../Libft/Libft/libft.h"
# include "../Libft/Libft/get_next_line.h"
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# define HEIGHT 1024
# define WIDTH 2048
# define MINIMAP_GRID 30

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
	float	x;
	float	y;
}	t_player;

/*
	Mlx and window pointer controller
	@param Mlx mlx pointer
	@param Window window pointer
*/
typedef struct s_mlxController
{
	void	*mlx;
	void	*window;
}				t_mlx;

typedef struct s_game
{
	char**	grid;
	char*	n_tex;
	char*	e_tex;
	char*	s_tex;
	char*	w_tex;
	int		floor;
	int		ceiling;
}	t_game;

void	my_mlx_pixel_put(t_img *data, int x, int y, int color);

#endif // !CUB3D_H
