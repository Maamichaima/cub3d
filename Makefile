NAME = cub3D
NAME_B = cub3D_bonus

SRC = main.c

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
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) ${LIBFT} $(GET_NEXT_LINE) -lXext -lX11 -lm -lmlx -o $(NAME)

bonus : $(NAME_B)

$(NAME_B): $(OBJ_B) $(LIBFT)
	$(CC) $(FLAGES) $(OBJ_B) -lXext -lX11 -lm -lmlx -o $(NAME_B)

$(LIBFT):
	make -s -C $(LIBFT_DIR)

clean :
	${RM} ${OBJ}
	make -s clean -C $(LIBFT_DIR)

fclean : clean
	make -s fclean -C $(LIBFT_DIR)
	${RM} ${NAME}
re: fclean all
