/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 12:06:01 by faventur          #+#    #+#             */
/*   Updated: 2022/10/06 16:52:33 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_UTILS_H
# define MLX_UTILS_H

# include <fcntl.h>
# include <sys/types.h>
# include <math.h>
# include <MLX42.h>
# include "libft.h"
# define WIDTH 640
# define HEIGHT 480

// ----------------------------------
// STRUCTS

/* vector with an x and y */
typedef struct s_vector
{
	int	x;
	int	y;
}				t_vector;

typedef struct s_vector2
{
	float	x;
	float	y;
}				t_vector2;

/* The 4 values that define a color */
typedef struct s_color {
	int	r;
	int	g;
	int	b;
	int	a;
}	t_color;

/* all info needed for an image */
typedef struct s_image {
	xpm_t		*texture;
	mlx_image_t	*img;
}				t_image;

typedef struct s_program {
	mlx_t					*mlx;
	t_image					img;
	t_image					*pixies;
	struct s_map			*map;
	uint32_t				frame;
	struct s_screen			*screen;
	struct s_render			*render;
	struct s_ray_casting	*rc;
	struct s_player			*player;
}				t_program;

typedef struct s_screen {
	int	width;
	int	height;
	int	half_width;
	int	half_height;
}				t_screen;

typedef struct s_render {
	uint32_t	delay;
}				t_render;

typedef struct s_ray_casting {
	float	increment_angle;
	float	precision;
}				t_ray_casting;

typedef struct s_player {
	float	fov;
	float	half_fov;
	float	x;
	float	y;
	float	angle;
}				t_player;

typedef struct s_map {
	char		**map;
	int			width;
	int			height;
}				t_map;

// to take out
typedef struct s_prop {
	int	start_pos;
}				t_prop;

typedef struct s_nme
{
	t_vector	pos;
	t_vector	prev;
}				t_nme;

typedef struct s_update
{
	t_vector	basic_pos;
	t_vector	villain_pos;
	int			b_var;
	int			v_var;
}				t_update;

// ---------------------------------
// FUNCTIONS

t_vector	ft_get_coordinates(char **map, char prop);
t_vector	ft_get_x_and_y(char **map, char prop);
t_vector	ft_get_char_pos(char **map);
char		who_is_it(char **map);
t_image		*ft_put_sprite(t_program *data);
void		ft_invoke_pixie(char c, uint32_t *i, t_program *data,
				t_image *pixie);
void		ft_invoke_char(t_program *data, t_image *pixie, t_vector pos,
				int var);
void		ft_invoke_enemy(t_program *data, t_image *pixie, t_vector pos,
				int var);
void		ft_display_map(t_program *data, t_image *pixie);

void		ft_display_moves(t_program *d, int key, t_vector pos, int *counter);
void		move_ur_ass(t_program *data);
void		track_ur_move_left(t_program *data, t_nme death);
void		track_ur_move_up(t_program *data, t_nme death);
void		track_ur_move_right(t_program *data, t_nme death);
void		track_ur_move_down(t_program *data, t_nme death);
int			ft_swing(t_program *data);

// window functions
int			ft_close(void);
void		fill_window(t_program *data, uint32_t color);

int			ft_map_parser(char **map);
char		**ft_map_reader(char *filename);

void		ft_input(int key, void *param);
void		ft_update(void *param);

void		ft_prop_init(t_prop *obj);

void		check(int argc, char **argv);
void		check_args(char argc);
void		check_map_extension(char *argv[]);
void		check_map_integrity(char *path);

void		ft_break_the_game(t_program *data, char *end_msg);

// drawing tools
void		mlx_draw_square(mlx_image_t *img, uint32_t width, uint32_t height,
				uint32_t color);
void		draw_line(mlx_image_t *img, t_vector2 start, t_vector2 finish,
				uint32_t color);
void		draw_vertical_line(mlx_image_t *img, t_vector draw_start,
				int draw_end, uint32_t color);

void		ray_casting(t_program *data);
float		degrees_to_radians(float degrees);

// vector utils
t_vector2	ft_floattovec2(float x, float y);
float		ft_vect2_distance_calc(t_vector2 start, t_vector2 finish);
void		ft_vec2_swap(t_vector2 *start, t_vector2 *finish);

#endif