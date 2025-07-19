NAME = fractol

SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

SRCS = $(wildcard $(SRC_DIR)/*.c)

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

CC = gcc
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -I$(INC_DIR) -Iminilibx-linux
LIBMLX = minilibx-linux/libmlx.a
LIBS = -Lminilibx-linux -lmlx -lXext -lX11 -lm

RM = rm -f

all: $(NAME)

$(NAME): $(LIBMLX) $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(NAME)

$(LIBMLX):
	$(MAKE) -C minilibx-linux

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR)
	$(MAKE) -C minilibx-linux clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C minilibx-linux clean

re: fclean all

.PHONY: all clean fclean re