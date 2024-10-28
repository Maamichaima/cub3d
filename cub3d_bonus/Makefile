#linux

# NAME = cub3D
# NAME_B = cub3D_bonus

# SRC = main.c parse_map.c textures.c check_color.c parse_textures.c check_all.c get_map.c lst.c draw.c key_hook.c casting_rays.c\
# 	cast_vertical.c render_3D.c mini_map.c textures_buffer.c
# SRC_B = 

# CFLAGS = #-fsanitize=address -g3 #-Wall -Wextra -Werror 

# CC = cc -g

# LIBFT_DIR = ./libft
# LIBFT = ./libft/libft.a
# GET_NEXT_LINE = ./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c

# OBJ = ${SRC:.c=.o}

# OBJ_B = ${SRC_B:.c=.o}
# all : ${NAME}

# $(NAME): $(OBJ) $(LIBFT)
# 	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) ${LIBFT} $(GET_NEXT_LINE) -lmlx_Linux -lXext -lm -lX11 -o $(NAME)
# bonus : $(NAME_B)

# $(NAME_B): $(OBJ_B) $(LIBFT)
# 	$(CC) $(FLAGES) $(OBJ_B) -lmlx_Linux -lXext -lX11  -o $(NAME_B)

# $(LIBFT):
# 	make -s -C $(LIBFT_DIR)

# clean :
# 	${RM} ${OBJ}
# 	make -s clean -C $(LIBFT_DIR)

# fclean : clean
# 	make -s fclean -C $(LIBFT_DIR)
# 	${RM} ${NAME}
# re: fclean all


# mac

NAME = cub3D

SRC = main.c parse_map.c textures.c check_color.c parse_textures.c check_all.c get_map.c lst.c draw.c key_hook.c casting_rays.c\
	cast_vertical.c render_3D.c mini_map.c animation.c garbage.c info_map.c slide.c move.c color_util.c\
	check_player.c initialize.c initialize_2.c mouse_hook.c check_rays.c check_wall.c cast_horizontal.c utils_0.c check_map.c\
	render_3D_util.c utils_1.c free_exit.c sound.c
OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

# MLX settings
MLX_DIR = ../mlx
LIBMLX = $(MLX_DIR)/libmlx.a
MLXFLAGS = -framework AppKit -framework OpenGL

# LIBFT settings
LIBFT_DIR = ../libft
LIBFT = $(LIBFT_DIR)/libft.a

# Get Next Line settings
GNL_SRC = ../get_next_line/get_next_line.c ../get_next_line/get_next_line_utils.c
GNL_OBJ = $(GNL_SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(LIBMLX)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(GNL_SRC) $(MLXFLAGS) $(LIBMLX) -o $(NAME)

$(LIBMLX):
	make -C $(MLX_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	$(RM) $(OBJ) $(OBJ_B) $(GNL_OBJ)
	make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME) $(NAME_B)
	make -C $(LIBFT_DIR) fclean

re: fclean all
