CC = gcc

FLAGS = -Wall -Wextra -Werror

SRC = $(shell find ./src -name "*.c")

OBJ = $(SRC:.c=.o)

NAME = Cub3D

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -Lmlx -lmlx -LLibft/Libft -lft -framework OpenGL -framework AppKit -o $(NAME)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
