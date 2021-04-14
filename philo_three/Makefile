NAME = philo_three

HEADER = philo.h

SRC = 	main.c \
		party.c \
		lib_utils.c \
		ft_strlen.c

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror -pthread -Os

%.o: %.c $(HEADER)
	gcc $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(FLAGS) $(OBJ) -o $(NAME) $(HEADER)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
