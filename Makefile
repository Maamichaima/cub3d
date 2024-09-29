NAME = cub3D
NAME_B = cub3D_bonus

SRC = main.c parse_map.c textures.c check_color.c parse_textures.c check_all.c get_map.c lst.c draw.c key_hook.c casting_rays.c\
	cast_vertical.c
SRC_B = 

CFLAGS = #-fsanitize=address -g3 #-Wall -Wextra -Werror 

CC = cc -g

LIBFT_DIR = ./libft
LIBFT = ./libft/libft.a
GET_NEXT_LINE = ./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c

OBJ = ${SRC:.c=.o}

OBJ_B = ${SRC_B:.c=.o}
all : ${NAME}

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) ${LIBFT} $(GET_NEXT_LINE) -lmlx_Linux -lXext -lm -lX11 -o $(NAME)
bonus : $(NAME_B)

$(NAME_B): $(OBJ_B) $(LIBFT)
	$(CC) $(FLAGES) $(OBJ_B) -lmlx_Linux -lXext -lX11  -o $(NAME_B)

$(LIBFT):
	make -s -C $(LIBFT_DIR)

clean :
	${RM} ${OBJ}
	make -s clean -C $(LIBFT_DIR)

fclean : clean
	make -s fclean -C $(LIBFT_DIR)
	${RM} ${NAME}
re: fclean all