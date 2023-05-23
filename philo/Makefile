SRC = philo.c philo_utils.c philo_utils2.c init.c philo_life.c states.c
OSRC = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=thread

NAME = philo
%.o : %.c philo.h
	cc -c $(CFLAGS) $<

all : $(NAME)
	
$(NAME) : $(OSRC)
	cc -pthread $(CFLAGS) $^ -o $(NAME)

fclean : 
	@rm -rf *.o $(NAME)
re : fclean all
