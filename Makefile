CC = cc
NAME = minikill
RDF = -lreadline
FLAGS = -Wall -Wextra -Werror #-fsanitize=address -g3
SRC = error/ft_err_handle_2.c error/ft_error_handling.c execution/env_building.c parsing/expanding_utils.c parsing/expanding_utils_2.c \
	parsing/expanding.c parsing/parsing_struct.c parsing/parsing_utils.c parsing/quotes_handle.c parsing/tokenization.c \
	utils/ft_char.c utils/ft_itoa.c utils/ft_lst_utils_1.c utils/ft_lst_utils_2.c utils/ft_putstr_fd.c utils/ft_strcmp.c \
	utils/ft_strdup.c utils/ft_strtrim.c minishell.c print_any.c execution/exec.c execution/execution.c utils/ft_split.c \
	builtin/cd.c builtin/echo.c builtin/env.c builtin/exit.c builtin/pwd.c builtin/unset.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c minishell.h
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(RDF) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean:
	rm -rf $(OBJ) $(NAME)

re: fclean all

.PHONY: all clean fclean re