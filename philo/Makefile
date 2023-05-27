SRC = philo.c philo_utils.c time_utils.c init.c init_utils.c philo_life.c states.c
OSRC = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror  #-fsanitize=thread

NAME = philo
%.o : %.c philo.h
	cc -c $(CFLAGS) $<

all : $(NAME)
	
$(NAME) : $(OSRC)
	cc -pthread $(CFLAGS) $^ -o $(NAME)

clean :
	@rm -rf *.o 
fclean : 
	@rm -rf *.o $(NAME)
re : fclean all

.PHONY : clean fclean all re
