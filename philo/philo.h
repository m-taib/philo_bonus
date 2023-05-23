#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct info
{
	int		i;
	int 	*info;
	int		is_dead;
	long	init_time;
	pthread_t 		*ptr_t;
	pthread_mutex_t *ptr_m;
	pthread_mutex_t *dead;
	pthread_mutex_t *write;
	pthread_mutex_t *lte;
} t_info;

typedef struct s_philo
{
	int				id;
	int				n_meals;
	long			last_meal;
	pthread_t 		*ptr_t;
	pthread_mutex_t *ptr_m;
	pthread_mutex_t *dead;
	pthread_mutex_t *write;
	struct info  	*philo_info;
	struct s_philo 	*next;
} t_philo;

void    *philo_routine(void *philo);
void	philos_create(t_philo *philos);
t_philo	*ft_new_philo();
void	ft_add_back(t_philo **philos, t_philo *newphilo);
void	create_philos_list(t_philo **philos, int n);
int	init(t_info *infos, t_philo **philos);

int    ft_usleep(t_philo *vars, int time);
int	is_num(char **av);
int	ft_atoi(char *str);
int     check_args(char **av, int ac, t_info *philo);
void	ft_clear(t_info *philo);
int		is_full(t_philo *philo);
void	supervisor(t_philo *philo);
long	get_time(void);
long	ft_interval(time_t before, time_t after);

/*****STATES*****/

void	think(t_philo *arg);
void	take_fork(t_philo *arg);
void	eat(t_philo *arg);
void	ft_sleep(t_philo *arg);

/****************/
enum
{
	philo_n, 
	time_to_die ,
	time_to_eat ,
	time_to_sleep ,
	ntp_must_eat
};
#endif
