/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:57:08 by mtaib             #+#    #+#             */
/*   Updated: 2023/05/27 18:32:58 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>

typedef struct info
{
	int				i;
	long			*info;
	int				is_dead;
	long			init_time;
	pthread_t		*ptr_t;
	pthread_mutex_t	*ptr_m;
	pthread_mutex_t	*dead;
	pthread_mutex_t	*write;
	pthread_mutex_t	*lte;
}					t_info;

typedef struct s_philo
{
	int				id;
	int				n_meals;
	long			last_meal;
	pthread_t		*ptr_t;
	pthread_mutex_t	*ptr_m;
	pthread_mutex_t	*dead;
	pthread_mutex_t	*write;
	struct info		*philo_info;
	struct s_philo	*next;
}					t_philo;

int					check_death(t_philo *arg);
void				*philo_routine(void *philo);
void				philos_create(t_philo *philos);
t_philo				*ft_new_philo(void);
void				ft_add_back(t_philo **philos, t_philo *newphilo);
void				create_philos_list(t_philo **philos, int n);
int					init(t_info *infos, t_philo **philos);

int					ft_usleep(t_philo *vars, int time);
int					is_num(char **av);
long				ft_atoi(char *str);
int					check_args(char **av, int ac, t_info *philo);
void				ft_clear(t_philo *philo);
int					is_full(t_philo *philo);
void				supervisor(t_philo *philo);
long				get_time(void);
long				ft_interval(time_t before, time_t after);
void				ft_lstclear(t_philo **lst);
void				free_mutexes(t_info *infos);
void				destroy_check(t_info *infos, int i);
/*****STATES*****/

void				think(t_philo *arg);
void				take_fork(t_philo *arg);
void				eat(t_philo *arg);
int					ft_sleep(t_philo *arg);

/****************/
enum
{
	philo_n,
	time_to_die,
	time_to_eat,
	time_to_sleep,
	ntp_must_eat
};
#endif
