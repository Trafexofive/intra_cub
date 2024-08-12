CC = cc

NAME = cub3D

CFLAGS = -Wextra -Wall -Werror -g

SRCS = raycasting/raycasting.c ./parse/parse/parse.c parse/p_entry.c\
	   ./parse/parse/utils.c main.c parse/garbage_collector/garb_col.c \
		parse/get_next_line/get_next_line.c parse/get_next_line/get_next_line_utils.c \
		parse/parse/linked_list.c parse/parse/parse2.c parse/parse/utils2.c parse/parse/parse3.c \
		parse/parse/utils4.c parse/parse/parse4.c parse/parse/utils3.c parse/parse/parse5.c \
		raycasting/texture_handle.c ./main_help.c utils/init.c \
		drawing/tool_kit.c raycasting/cast.c physics/movement_and_collision.c

OBJS = ${SRCS:.c=.o}

HEADERS = inc/cub.h inc/defines.h inc/draw.h inc/garbage.h \
			inc/get_next_line.h inc/macros.h inc/raycast.h \
			inc/struct.h inc/utils.h

all : $(NAME)

%.o: %.c $(HEADERS)
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

$(NAME): $(OBJS) 
	$(CC) $(OBJS) -oFast -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re 

