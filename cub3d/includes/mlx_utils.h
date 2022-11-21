/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 12:06:01 by faventur          #+#    #+#             */
/*   Updated: 2022/11/17 12:32:25 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_UTILS_H
# define MLX_UTILS_H

# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <math.h>
# include <sys/time.h>
# include <MLX42.h>
# include "libft.h"
# include "miniaudio.h"
# define WIDTH 640
# define HEIGHT 480
# define BPP 4
# define KILLCOUNTDOWN 5
# define MOVECOUNTDOWN 10
# define MINDISTANCE 6
# define JUMPSCARE_FREQ 30
# define MINIAUDIO_IMPLEMENTATION

typedef struct s_vector
{
	int	x;
	int	y;
}				t_vec;

typedef struct s_vector2
{
	double	x;
	double	y;
}				t_vec2;

typedef struct s_vector3
{
	uint32_t	x;
	uint32_t	y;
}				t_vec3;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	a;
}				t_color;

typedef struct s_camera
{
	double		camera_x;
	t_vec2		plane;
	t_vec2		dir;
	t_vec2		pos;
}				t_camera;

typedef struct s_door_data
{
	int		is_door;
	int		sliding;
	int		index;
	double	offset;
	t_vec	map_pos;
	double	opening_timer;
}				t_door_data;

typedef struct s_door
{
	t_door_data	**door_map;
	size_t		nb_doors;
	size_t		count;
}				t_door;

typedef struct s_image
{
	xpm_t		*texture;
	mlx_image_t	*img;
	t_vec2		size;
}				t_image;

typedef struct s_sprite
{
	double	x;
	double	y;
	int		texture;
}				t_sprite;

typedef struct s_minimap
{
	t_vec2		pos;
	mlx_image_t	*img;
}			t_minimap;

typedef struct s_map
{
	char		**map;
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	char		*ceiling_texture;
	char		*floor_texture;
	t_color		floor_color;
	t_color		ceiling_color;
	int			mode;
	t_vec		spawn_pos;
	char		dir;
	t_minimap	*minimap;
	t_vec		size;
	char		*map_str;
	int			*size_arr;
	int			buf_size;
}				t_map;

typedef struct s_mouse
{
	double		pcos;
	double		psin;
	double		ncos;
	double		nsin;
	int			focus;
}			t_mouse;

typedef struct s_key_hook
{
	double		pcos;
	double		psin;
	double		ncos;
	double		nsin;
}				t_key_hook;

typedef struct s_sprite_caster
{
	t_vec2		sprite;
	t_vec2		transform;
	double		inv_det;
	int			sprite_screen_x;
	int			sprite_width;
	int			sprite_height;
	t_vec		draw_start;
	t_vec		draw_end;
	int			stripe;
	int			d;
	t_vec		tex;
	t_sprite	*sprites;
	int			*order;
	double		*sprite_dist;
	double		*z_buffer;
}				t_s_caster;

typedef struct s_floor_casting
{
	t_vec2	ray_dir0;
	t_vec2	ray_dir1;
	int		p;
	double	pos_z;
	double	row_distance;
	t_vec2	floor_step;
	t_vec2	floor;
	t_vec	cell;
	t_vec	t;
	int		floor_tex;
	int		ceiling_tex;
}				t_floor;

typedef struct s_ray_data
{
	t_vec2		resolution;
	t_camera	camera;
	t_vec2		ray_dir;
	t_vec		map_pos;
	t_vec2		ray_side;
	t_vec2		ray_delta;
	t_vec		step_coord;
	int			hit;
	int			side;
	double		wall_distance;
	int			line_height;
	int			draw_start;
	int			draw_end;
	t_vec		tex;
	int			text_select;
	double		wall_x;
	double		wall_x_offset;
	double		wall_y_offset;
	double		step;
	double		tex_pos;
	int			ray_tex;
	t_floor		fl;
	t_key_hook	k;
	t_mouse		m;
	int			half_width;
	t_map		*map;
	t_s_caster	sprite;
	uint32_t	**tex_buf;
	t_door		door;
}				t_ray;

typedef struct s_speed
{
	double		movement;
	double		rotation;
}				t_speed;

typedef struct s_player
{
	char		player_spawn_dir;
	t_vec		player_spawn_pos;
	int			fov;
	t_speed		speed;
	double		yaw;
	int			start_direction;
	double		footstep_timer;
	int			footstep_lock;
	size_t		collected;
}				t_player;

typedef struct s_enemy
{
	t_vec2		pos;
	t_vec		*valid_pos;
	size_t		valid_pos_n;
	double		kill_timer;
	double		move_timer;
	double		selena_timer;
	double		yoshie_timer;
	int			kill_countdown;
	int			move_countdown;
	int			disable_ai;
	t_image		*warning_text;
	t_image		*death_bg;
	t_image		*death_text;
	int			alive;
	int			lock;
}				t_enemy;

typedef struct s_screen
{
	t_image		display;
}				t_screen;

typedef struct s_hud
{
	t_image	*sprites;
	size_t	pos;
}				t_hud;

typedef struct s_audio
{
	ma_engine	*audio_engine;
	ma_sound	ambiance;
	ma_sound	creeping_down;
	ma_sound	unraveled;
	ma_sound	scare;
	ma_sound	*dead;
	ma_sound	*death;
	ma_sound	*suspense;
	ma_sound	*smiler;
	ma_sound	*behind_you;
	ma_sound	*footstep;
	ma_sound	geiger;
	ma_sound	*door;
	ma_sound	pickup;
	int			lock;
	int			lock2;
	double		volume;
}				t_audio;

typedef struct s_shading
{
	double	multiplier;
	double	distance;
	double	ratio;
	double	timer;
	int		shading_lock;
}				t_shading;

typedef struct s_quest
{
	size_t		n_pages;
	t_image		*pickup;
	t_image		*exit;
	t_image		*exit_key;
	t_image		*exit_win;
	t_image		*exit_bg;
	size_t		n_pickup;
	int			done;
	t_vec		exit_pos;
}				t_quest;

typedef struct s_data
{
	mlx_t			*mlx;
	t_map			*map;
	t_screen		screen;
	uint32_t		render_delay;
	uint32_t		img_index;
	t_image			*textures;
	t_player		player;
	t_ray			ray_data;
	int				keycode;
	int				fd;
	int				key;
	int				delay;
	int				time;
	double			timer;
	int				exit;
	t_enemy			enemy;
	t_hud			hud;
	t_quest			quest;
	t_audio			audio;
	t_shading		shading;
}				t_data;

typedef struct s_var
{
	double		old_dir_x;
	double		old_plane_x;
	double		rotation;
	double		movement;
	double		alpha;
	double		slide;
	uint32_t	width;
	uint32_t	height;
	uint32_t	color;
	int			x;
	int			y;
	uint8_t		*pixels;
	uint32_t	i;
	uint32_t	j;
}				t_var;

typedef struct s_getcolor
{
	ssize_t	i;
	ssize_t	j;
	ssize_t	k;
	char	**colors;
	t_color	rgba;
}			t_getcolor;

typedef struct s_ctexture
{
	char	str[2];
	int		index;
}			t_ctexture;

typedef struct s_shape
{
	int		x;
	int		y;
	int		width;
	int		height;
	double	dim;
	t_image	*img;
}				t_shape;

// init
void		init_sprites(t_data *data, t_ray *ray);
void		init_sprites_pos(t_data *data, t_ray *ray);
void		init_minimap(t_data *data);
void		init_struct(t_data *data);
void		init_direction(t_data *data);
void		init_enemy(t_data *data);
void		init_enemy_texture(t_data *data, t_image *texture);
void		init_hud(t_data *data);
void		init_hud_draw(t_data *data);
void		init_doors(t_data *data);
void		init_door_texture(t_data *data, t_image *texture);
void		init_audio(t_data *data);
void		init_audio_behind_you(t_data *data, ma_result *result);
void		init_audio_player(t_data *data, ma_result *result);
void		init_audio_ambiance(t_data *data, ma_result *result);
void		init_audio_suspense(t_data *data, ma_result *result);
void		init_audio_doors(t_data *data, ma_result *result);
void		*init_textures(t_data *data);
void		init_quest(t_data *data);
void		init_quest_walls(t_data *data, t_image *texture);

// window functions
void		mlx_draw_square(mlx_image_t *img, uint32_t width, uint32_t height,
				uint32_t color);
void		fill_window(t_data *data, uint32_t color);

// hooks
void		key_input(t_data *data);
void		update_key(mlx_key_data_t keydata, void *param);
void		key_input_arrows(t_data *data, t_ray *ray, t_var *var);
void		mouse_input(double x, double y, void *param);
void		update_render(void *param);

// parsing functions
char		**ft_map_reader(char *filename);
t_map		*check(int argc, char **argv);
void		check_args(char argc);
void		check_map_extension(char *argv[]);
t_map		*check_map_integrity(char *path);
int			check_map_components(char **map);
char		**get_map_description(char **map);
int			get_color(char *str, t_map *mapStruct, int mode);
int			get_color_check(char **colors, ssize_t j);
int			get_texture(char *str, t_map *mapStruct, int mode);
int			invalid_check(char **map);
int			wall_check(char **map);
int			gap_check(char **map);
int			gap_check_reverse(char **map, ssize_t i, ssize_t j);
int			space_check(char **map, ssize_t i, ssize_t j);
int			hole_check(char **map);
int			check_texture(t_map *m, char *map, int *count, t_ctexture c);
int			check_texture_batch(t_map *m, char **map, size_t i, int *count);
int			get_spawn_position(t_map *m);
void		init_direction(t_data *data);

// ray casting tools
void		floor_casting(t_data *data, t_ray *ray);
void		ray_casting(t_data *data);
void		ray_data_init(t_ray *ray, int x);
void		ray_delta_calculator(t_ray *ray);
void		rayside_calculator(t_ray *ray);
void		ray_launcher(t_ray *ray);
void		ft_check_walls(t_ray *ray);
void		door_complement(t_ray *ray);
void		door_complement_pt2(t_ray *ray);
void		check_door(t_ray *ray);
void		wall_distance_calculator(t_ray *ray);
void		wall_line_calculator(t_ray *ray);
void		texture_x_pos_calculator(t_data *data, t_ray *ray);
void		texture_y_pos_calculator(t_data *data, t_ray *ray);
void		choose_wall_texture(t_ray *ray);
void		sprite_caster(t_data *data, t_ray *ray, t_var *v);
uint32_t	get_shading(t_data *data, uint32_t color, double distance);

// events
int			update_events(t_data *data);
void		update_quest(t_data *data);
void		update_enemy(t_data *data, t_ray *ray);
void		update_doors(t_data *data, t_ray *ray);
void		show_death(t_data *data);
int			check_collision(t_data *data, t_var *var, int mode);

// drawing tools
void		draw_line(mlx_image_t *img, t_vec2 start, t_vec2 finish,
				uint32_t color);
void		draw_vertical_line(mlx_image_t *img, t_vec3 draw_start,
				uint32_t draw_end, uint32_t color);
void		draw_walls(t_data *data, int x);
void		draw_ceiling(t_data *data, int x);
void		draw_floor(t_data *data, int x);
void		draw_minimap(t_data	*data);
void		draw_death(t_data *data);
void		update_move(t_data *data);
void		draw_rect(mlx_image_t *img, t_shape rect, int color);

// sprites
void		load_sprites(t_data *data, t_image *texture);
void		ft_load_fireset_textures(t_data *data, t_image *texture);
void		sort_sprites(int *order, double *dist, int amount);

// pathfinding
void		pathfinding_list_pos(t_data *data);
t_vec		pathfinding_get_pos(t_data *data);
t_vec2		pathfinding_pos_dist(t_data *data, t_vec2 start, t_vec2 end,
				size_t min);
t_vec2		pathfinding_pos_except(t_data *data, t_vec2 pos, size_t	distance);
t_vec2		pathfinding_pos_close(t_data *data, t_vec2 pos, int distance);
void		pathfinding_dist_check(t_data *data, size_t min);

// minimap
void		get_map_size(t_data *data);
void		get_map_str(t_data *data);
void		get_size_arr(t_data *data, int y);
int			minimap_get(t_map *map, int x, int y);

// vector utils
t_vec		ft_inttovec(int x, int y);
t_vec2		ft_doubletovec2(double x, double y);
double		ft_vect2_distance_calc(t_vec2 start, t_vec2 finish);
void		ft_vec_swap(t_vec *start, t_vec *finish);
void		ft_vec2_swap(t_vec2 *start, t_vec2 *finish);

// color tools
t_color		new_color(int r, int g, int b, int a);
t_color		hex_to_rgb(uint32_t hex_value);
t_color		lerp(t_color a, t_color b, double t);
double		lerp_double(double a, double b, double t);
double		inv_lerp(double a, double b, double value);
int			get_rgba(int r, int g, int b, int a);
int			rgb_to_hex(t_color rgb);
int			add_shade(double distance, int color);
int			get_opposite(int color);
void		turn_pixel_to_color(char *pixel, t_color color);
void		turn_img_to_color(t_image *image, t_color color);

// free
void		free_exit(t_data *data);
void		close_hook(void *data);
void		free_data(t_data *data);
void		free_audio(t_data *data);
void		free_audio_behind_you(t_data *data);
void		free_audio_player(t_data *data);
void		free_audio_ambiance(t_data *data);
void		free_audio_suspense(t_data *data);
void		free_textures(t_data *data);

// utils
void		ft_uchar_arr_display(unsigned char *arr, size_t size);
uint32_t	*uchar_to_arr(unsigned char *arr, size_t width,
				size_t height);
uint32_t	**hex_buf_creator(uint32_t *arr, size_t width, size_t height);
uint32_t	**ft_from_uchar_to_hex_buf(unsigned char *arr, size_t width,
				size_t height);
t_color		**rgb_buf_creator(uint32_t **buf, size_t width, size_t height);
t_color		**ft_from_uchar_to_rgb_buf(unsigned char *arr, size_t width,
				size_t height);
void		ft_print_map(char **map);
double		get_time(void);
void		update_time(struct timeval *tv, long long *timestamp);
int			get_delay(int startnow, int min);
void		tex_to_img(t_data *data, t_image *texture, size_t i);
void		free_door_arrays(t_ray *ray, size_t size);
void		free_door_arrays_index(t_ray *ray, size_t index, size_t size);
t_vec		ft_get_coordinates(char **map, char prop);
t_vec		ft_get_x_and_y(char **map, char prop);
int			is_wasd(t_data *data);
double		check_double_overflow(double value);

#endif