SRC = philo_bonus.c philo_utils.c time_utils.c init.c states.c philo_life.c
OSRC = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address 

NAME = philo_bonus
%.o : %.c philo.h
	cc -c $(CFLAGS) $<

all : $(NAME)
	
$(NAME) : $(OSRC)
	cc -pthread $(CFLAGS) $^ -o $(NAME)

fclean : 
	@rm -rf *.o $(NAME)
re : fclean all
