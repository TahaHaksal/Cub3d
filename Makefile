RED				=	"\033[0;31m"
GREEN			=	"\033[0;32m"
YELLOW			=	"\033[0;33m"
CYAN			=	"\033[0;35m"
BLUE			=	"\033[0;36m"
END				=	"\033[0;0m"

NAME = cub3D

CC = gcc
FLAGS = -Wall -Wextra -Werror

SRC = $(shell find ./src -name "*.c")
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -Lmlx -lmlx -LLibft/Libft -lft -framework OpenGL -framework AppKit -o $(NAME)
	@echo $(GREEN)	"Compilation complete" $(END)

clean:
	@echo $(YELLOW) "Removing object files..." $(END)
	@rm -rf $(OBJ)
	@echo $(RED) "$(OBJ) deleted"$(END) $(GREEN)"successfully!\n" $(END)

fclean:
	@echo $(YELLOW) "Removing object files and $(NAME)..." $(END)
	@rm -rf $(OBJ)
	@rm -rf $(NAME)
	@echo $(RED) "$(OBJ) deleted"$(END)
	@echo $(RED) "$(NAME) deleted"$(END) $(GREEN)"successfully!\n" $(END)

re: fclean all

.PHONY: all fclean clean re
