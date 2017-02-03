NAME = fdf

SRCS = ./src/main.c \
		./src/get.c \
		./src/draw.c \
		./src/rot.c \

OBJS = $(SRCS:.c=.o)

INCLUDE = -I./src \
			-I./libft \
			-I./minilibx_macos \
			-I./ft_printf

LINK = -L./minilibx_macos/ -framework OpenGL -framework AppKit minilibx_macos/libmlx.a \
	   ./ft_printf/libftprintf.a \
	   ./libft/libft.a \

CC = gcc

CFLAGS = -Wall -Wextra -Werror -o

all: allmakes $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(NAME) $(SRCS) $(INCLUDE) $(LINK)

allmakes: mlxmake printfmake libftmake

mlxmake:
	cd ./minilibx_macos && $(MAKE)

printfmake:
	cd ./ft_printf && $(MAKE)

libftmake:
	cd ./libft && $(MAKE)

clean:
	/bin/rm -f $(OBJS)

fclean : clean
	/bin/rm -f $(NAME)

re: fclean all