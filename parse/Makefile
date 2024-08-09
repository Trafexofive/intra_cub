SRCS = ./parse/parse.c ./parse/utils.c main.c ./garbage_collector/garb_col.c \
		./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c \
		./parse/linked_list.c ./parse/parse2.c ./parse/utils2.c ./parse/parse3.c \
		./parse/utils4.c ./parse/parse4.c ./parse/utils3.c ./parse/parse5.c


OBJS = $(SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

RM = rm -f

NAME = cub3D

HEADERS = ./parse/cube.h ./garbage_collector/garbage.h ./get_next_line/get_next_line.h


all : $(NAME)


$(NAME) : $(OBJS)
	$(CC) $(OFLAGS) -Lmlx -lmlx -framework OpenGL -framework AppKit $(OBJS) -o $(NAME)

%.o: %.c $(HEADERS)
	$(CC) $(CFlAGS) -Imlx -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY: clean
