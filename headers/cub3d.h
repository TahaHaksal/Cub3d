/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaksal <mhaksal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 08:55:22 by mhaksal           #+#    #+#             */
/*   Updated: 2023/01/20 08:55:22 by mhaksal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# define MINIMAP_H 255
# define MINIMAP_W 255
# define FOV 60
# define ROT_SPEED 0.05
# define MOV_SPEED 0.15
# define COL 0.5

typedef struct s_2dintVector
{
	int	x;
	int	y;
}	t_i;

typedef struct s_2dVector
{
	double	x;
	double	y;
}	t_v;

typedef struct s_rayVals
{
	t_v	ray_dir;
	t_v	map;
	t_v	side;
	t_v	step;
	t_v	delta;
	t_v	wall;
}	t_rayVals;

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
	int		mouse_first;
	int		mouse_last;
	int		mini_map;
	int		max_len;
	int		max_h;
	int		cursor;
	int		floor;
	int		row;
	int		ceiling;
	void	*weapon;
	char	*tex_paths[4];
	char	**grid;
	t_i		*image_sizes;
	t_i		tex;
	t_img	*textures;
}	t_game;

typedef struct s_mlxController
{
	void		*mlx;
	void		*window;
	t_img		*image;
	t_player	*player;
	t_game		*game;
}	t_mlx;

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
void	checkMap(char *path);
char	**map_control(char *path, t_v *j_len, int j, int i);
void	top_bottom_check(char **M, int i, int j, int len);
void	right_left_check(char **M, int i, int j, int len);
void	character_check(char **M, int i, int j);
double	map(double value, double from_high, double to_low, double to_high);
int		norm(double x, double y);
void	error(char *str);
int		close_exit(t_mlx *vars);
void	map_free(char **Map, int j);

char	*ft_strpbrk(char *string, char *set);
int		char_to_index(char c, t_player *player);
int		str_to_colour(char *str);

int		keyhandler(int keycode, t_mlx *mlx);
int		mouse_move(int x, int y, t_mlx *mlx);
void	calc_rotation(t_player *player, char sign);
void	calc_movement_f(t_mlx *mlx);
void	calc_movement_b(t_mlx *mlx);
void	calc_movement_l(t_mlx *mlx);
void	calc_movement_r(t_mlx *mlx);

void	draw_scene(t_img *img, t_game *game, t_player *player, t_mlx *mlx);
void	vert_line(int x, t_img *img, t_img *tex, t_draw_wall w);
void	draw_square(t_img *img, double x, double y, int colour);
void	draw_minimap(t_img *img, t_game *game, t_player *player, t_mlx *mlx);
int		draw_map(t_mlx *mlx);
void	diagonal_line(t_v start, t_v end, t_img *img, t_mlx *mlx);
void	draw_target(t_mlx *mlx);
void	draw_ceil_and_floor(t_mlx *mlx, int x, int y);
void	my_mlx_pixel_put(t_img *data, int x, int y, unsigned int color);
int		get_trgb(int t, int r, int g, int b);

t_v		calc_dda(t_mlx *mlx, t_v map, t_v sideDist, t_rayVals step_dd);
void	calc_delta_dist(t_v raydir, t_v *delta_dist);
void	calc_sides(t_player *player);
void	calc_diagonal_line(t_img *img, t_player *player, t_mlx *mlx);

int		pick_dir(t_v wall, t_v ray_dir);
int		pick_tex_x(int i, t_rayVals ray, t_player *p, t_game *game);

#endif
