/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 15:53:39 by mtaib             #+#    #+#             */
/*   Updated: 2023/05/27 18:41:13 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>
# include <limits.h>

typedef struct philo
{
	int			i;
	long		*info;
	int			nb_to_eat;
	int			is_dead;
	long		init_time;
	sem_t		*sem;
	sem_t		*sem_death;
	sem_t		*sem_lte;
	sem_t		*sem_eat;
	sem_t		*sem_print;
	pthread_t	th;
	int			*ids;
	long		eating_time;
}				t_philo;

int				init(t_philo *philo);
void			*supervisor(void *philo);
void			ft_usleep(t_philo *vars, int time);
int				is_num(char **av);
long			ft_atoi(char *str);
int				check_args(char **av, int ac, t_philo *philo);
void			philo_routine(t_philo *philo);
void			philos_create(t_philo *ptr);
void			ft_clear(t_philo *philo);
int				is_full(t_philo *philo);
int				init(t_philo *philo);
long			get_time(void);
long			ft_interval(time_t before, time_t after);
void			ft_close(t_philo *philo);
/****STATES****/
void			think(t_philo *arg);
void			take_fork(t_philo *arg);
void			eat(t_philo *arg);
void			ft_sleep(t_philo *arg);
void			eating_phase(t_philo *arg);

/**************/
enum
{
	philo_n,
	time_to_die,
	time_to_eat,
	time_to_sleep,
	ntp_must_eat
};
#endif
