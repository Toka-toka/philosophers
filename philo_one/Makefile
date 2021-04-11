NAME = philo_one

SRC = *.c

OBJ = $(SRC:.c=.o)

FLAGS = -pthread -Os

#-Wall -Wextra -Werror 

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(FLAGS) $(SRC) -o $(NAME) -g

#%.o: %.c $(INCLUDE)
#	@gcc $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
