
CC := cc

NAME := cub3d

CFLAGS := -Wextra -Wall -Werror -g

DRAW := drawing/tool_kit.c raycasting/cast.c physics/movement_and_collision.c

UTILS := utils/init.c

HEADERS = ./parse/cube.h ./garbage_collector/garbage.h ./get_next_line/get_next_line.h

SRCS = raycasting/raycasting.c $(DRAW) $(UTILS) ./parse/parse/parse.c parse/p_entry.c\
	   ./parse/parse/utils.c main.c parse/garbage_collector/garb_col.c \
		parse/get_next_line/get_next_line.c parse/get_next_line/get_next_line_utils.c \
		parse/parse/linked_list.c parse/parse/parse2.c parse/parse/utils2.c parse/parse/parse3.c \
		parse/parse/utils4.c parse/parse/parse4.c parse/parse/utils3.c parse/parse/parse5.c \
		raycasting/texture_handle.c

OBJS := ${SRCS:.c=.o}


all : $(NAME)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

$(NAME): $(OBJS) 
	$(CC) $(OBJS) -oFast -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re 

