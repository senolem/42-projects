# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albaur <albaur@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/16 11:47:12 by faventur          #+#    #+#              #
#    Updated: 2022/11/17 12:30:12 by albaur           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3d
ARGS		=	map.cub
CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror -g3
LINKS		=	-lglfw -L /Users/${USER}/goinfre/.brew/opt/glfw/lib/ #-ldl -lm -pthread #linuxflags
LIBLINKS	=	-I./MLX42/include/MLX42 -I./includes -I./libft/includes -I/Users/${USER}/goinfre/.brew/opt/glfw/include
SRC_PATH	=	srcs/
OBJ_PATH	=	bin/
C_EXTENSION	=	.c

MAIN_PATH	=	main/
MAIN_FILES	=	main
SRCS_FILES	+=	$(addprefix $(MAIN_PATH), $(MAIN_FILES))

INIT_PATH	=	init/
INIT_FILES	=	init_struct init_direction init_minimap init_sprites init_hud \
				init_textures init_textures2 init_doors init_audio init_audio_batch \
				init_quest
SRCS_FILES	+=	$(addprefix $(INIT_PATH), $(INIT_FILES))

PARSE_PATH	=	parsing/
PARSE_FILES	=	check check_map check_map_utils check_map_utils2 gap_check \
				gap_check_reverse get_color get_color2 get_texture hole_check \
				invalid_check wall_check get_spawn_position
SRCS_FILES	+=	$(addprefix $(PARSE_PATH), $(PARSE_FILES))

MLX_PATH	=	mlx_tools/
MLX_FILES	=	window colours colour_conversions
SRCS_FILES	+=	$(addprefix $(MLX_PATH), $(MLX_FILES))

PF_PATH		=	pathfinding/
PF_FILES	=	pathfinding pathfinding_except
SRCS_FILES	+=	$(addprefix $(PF_PATH), $(PF_FILES))

UTILS_PATH	=	utils/
UTILS_FILES	=	ft_map_reader drawing_tools utils ft_from_uchar_to_rgb_buf \
				vec_utils time door_utils is_wasd
SRCS_FILES	+=	$(addprefix $(UTILS_PATH), $(UTILS_FILES))

RC_PATH		=	raycasting/
RC_FILES	=	update_render ray_casting_tools wall_casting \
				wall_casting2 door_complement floor_ceiling_textures \
				floor_ceiling_casting sprite_casting
SRCS_FILES	+=	$(addprefix $(RC_PATH), $(RC_FILES))

EVENTS_PATH		=	events/
EVENTS_FILES	=	events enemy death doors move quest
SRCS_FILES		+=	$(addprefix $(EVENTS_PATH), $(EVENTS_FILES))

INPUT_PATH	=	input/
INPUT_FILES	=	key_input mouse_input other_input check_collision
SRCS_FILES	+=	$(addprefix $(INPUT_PATH), $(INPUT_FILES))

MAP_PATH	=	minimap/
MAP_FILES	=	draw_minimap minimap_utils
SRCS_FILES	+=	$(addprefix $(MAP_PATH), $(MAP_FILES))

FREE_PATH	=	free/
FREE_FILES	=	free free_audio free_audio_batch free_textures
SRCS_FILES	+=	$(addprefix $(FREE_PATH), $(FREE_FILES))

OBJS	= $(addprefix srcs/, ${SRCS:.c=.o})

RM	=	rm -f

SRCS_FILES_EXT	+=	$(addsuffix $(C_EXTENSION), $(SRCS_FILES))

SRCS			+=	$(addprefix $(SRC_PATH), $(SRCS_FILES_EXT))

OBJS			=	$(addprefix $(OBJ_PATH), $(SRCS_FILES_EXT:c=o))

NONE	= \033[0m
HIGREEN	= \033[92m
HIBLUE	= \033[94m
CURSIVE	= \033[3m

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -sC ./libft
	@$(MAKE) -sC ./MLX42
	@mv ./libft/libft.a .
	@mv ./MLX42/libmlx42.a .
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS) libft.a libmlx42.a $(LINKS) -fsanitize=address
	@echo "$(CURSIVE)$(HIBLUE)If you're not careful and you noclip out of reality in the wrong areas,$(NONE)"
	@echo "$(CURSIVE)$(HIBLUE)you'll end up in the Backrooms, where it's nothing but the stink of old$(NONE)"
	@echo "$(CURSIVE)$(HIBLUE)moist carpet, the madness of mono-yellow, the endless background noise$(NONE)"
	@echo "$(CURSIVE)$(HIBLUE)of fluorescent lights at maximum hum-buzz, and approximately six hundred$(NONE)"
	@echo "$(CURSIVE)$(HIBLUE)million square miles of randomly segmented empty rooms to be trapped in.$(NONE)"
	@echo "$(CURSIVE)$(HIBLUE)God save you if you hear something wandering around nearby, because it's$(NONE)"
	@echo "$(CURSIVE)$(HIBLUE)sure as hell it has heard you.$(NONE)"
	@echo "$(CURSIVE)$(NONE)Anonymous user, 4chan$(NONE)"

.c.o:
	@$(CC) $(FLAGS) -c $(LIBLINKS) $< -o ${<:.c=.o}

$(OBJ_PATH)%.o: $(SRC_PATH)%.c 
	@mkdir -p $(dir $@)
	${CC} ${FLAGS} ${LIBLINKS} -c $< -o $@

exe: all
	@./$(NAME) $(ARGS)

clean:
	@$(RM) -r libft.a libmlx42.a $(OBJ_PATH)
	@$(MAKE) clean -C ./libft

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) fclean -C ./libft

re: fclean all

relib: fclean
	@$(MAKE) re -sC ./MLX42
	@$(MAKE) all

.PHONY: all exe clean fclean re