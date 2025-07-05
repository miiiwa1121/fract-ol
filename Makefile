NAME = fractol

SRCS = main.c init.c events.c utils.c fractols.c render.c

OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I. -Iminilibx-linux
LIBMLX = minilibx-linux/libmlx.a
LIBS = -Lminilibx-linux -lmlx -lXext -lX11 -lm

all: $(LIBMLX) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(NAME)

$(LIBMLX):
	$(MAKE) -C minilibx-linux

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C minilibx-linux clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C minilibx-linux clean

re: fclean all

.PHONY: all clean fclean re
