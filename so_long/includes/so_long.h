/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 18:42:24 by albaur            #+#    #+#             */
/*   Updated: 2022/04/28 13:49:55 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

// librairies
# include <mlx.h>
# include <fcntl.h>
# include "../libft/libft.h"

// variables
# define T_S 63
# define MAX_OFFSET 6300

// structures

typedef struct s_component
{
	int					x;
	int					y;
	struct s_component	*next;
}		t_component;

typedef struct s_sprite
{
	struct s_sprite		*head;
	void				*img;
	struct s_sprite		*next;
}		t_sprite;

typedef struct s_storage
{
	t_component		*storage;
	t_sprite		*sprite;
}		t_storage;

typedef struct s_map
{
	char	**map;
	int		columns;
	int		rows;
	int		p_nb;
	int		c_nb;
	int		e_nb;
}		t_map;

typedef struct s_player
{
	int			health;
	int			x;
	int			y;
	t_sprite	*idle;
	t_sprite	*sprite;
	t_sprite	*u_idle;
	t_sprite	*u_move;
	t_sprite	*d_idle;
	t_sprite	*d_move;
	t_sprite	*l_idle;
	t_sprite	*l_move;
	t_sprite	*r_idle;
	t_sprite	*r_move;
}		t_player;

typedef struct s_tiles
{
	void	*wall;
	void	*floor;
	void	*exit;
	void	*open_exit;
}		t_tiles;

typedef struct s_hud
{
	void		*img;
	t_sprite	*num;
	t_sprite	*health;
}		t_hud;

typedef struct s_enemy
{
	void	*img;
}		t_enemy;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			is_moving;
	int			offset;
	int			steps;
	t_map		map;
	t_tiles		tiles;
	t_player	player;
	t_storage	storage;
	t_hud		hud;
	t_enemy		enemy;
}		t_data;

// sanity check
void		ext_check(char *fileName);
void		char_check(char *str);
void		len_check(char *str, int len);
void		wall_check(t_map *map, int i);
void		min_check(t_map *map);
void		error_handler(char *str);

// initialization
void		window_init(t_data *data);
void		img_init(t_data *data);
void		game_init(t_data *data);
void		render_init(t_data *data);
void		map_init(t_map *map, char *str);

// map
void		map_read(t_data *data, char *fileName);
char		*gnl_map(int fd);
void		*ft_ptr_realloc(void *buffer, int before_size, int after_size);
void		map_parse(t_data *data, char *fileName);
void		count_component(t_map *map);

// hook
int			close_hook(t_data *data);
int			key_hook(int key, t_data *data);
int			loop_hook(t_data *data);

// rendering
void		*xpm_to_img(t_data *data, char *path);
void		img_to_sprite(t_data *data, t_sprite **sprite, char *img, int c);
void		set_player_sprite(t_data *data);
void		render_exit(t_data *data);
void		render_tiles(t_data *data);
void		render_sprites(t_data *data);
void		render_player_animate(t_data *data);
void		render_item_animate(t_data *data);
void		render_hud(t_data *data);
void		render_hud_health(t_data *data);
void		render_enemies(t_data *data);
void		render_refresh(t_data *data);
void		put_mlx(t_data *data, void *img, int x, int y);

// movement
void		move(int key, t_data *data);
void		collision_wall(t_data *data, int x, int y);
void		collision_item(t_data *data, int x, int y);
void		collision_exit(t_data *data, int x, int y);
void		collision_enemy(t_data *data, int x, int y);
void		collision_manage(t_data *data, int x, int y);

// lst utils
void		ft_lstc_delete(t_component **lst, int x, int y);
int			ft_lstc_add(t_component **lst, int x, int y);
void		ft_lstc_add_back(t_component **lst, t_component *new);
t_component	*ft_lstc_last(t_component *component);
void		get_back_to_head(t_data *data);

#endif
