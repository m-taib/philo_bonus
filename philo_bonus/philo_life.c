/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 16:16:34 by mtaib             #+#    #+#             */
/*   Updated: 2023/05/27 19:06:03 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_death(t_philo *arg)
{
	int		i;

	i = -1;
	sem_wait(arg->sem_lte);
	if (ft_interval(arg->eating_time, get_time()) >= arg->info[time_to_die])
	{
		sem_wait(arg->sem_print);
		printf("%ld %d died\n",
			ft_interval(arg->init_time, get_time()), arg->i + 1);
		arg->is_dead = 1;
		while (++i < arg->info[philo_n])
			sem_post(arg->sem_eat);
		sem_post(arg->sem_death);
	}
	sem_post(arg->sem_lte);
}

void	*supervisor(void *philo)
{
	t_philo	*arg;
	int		j;

	j = 0;
	arg = (t_philo *)philo;
	while (1)
	{
		check_death(arg);
		sem_wait(arg->sem_lte);
		if (arg->info[ntp_must_eat]
			&& arg->nb_to_eat == arg->info[ntp_must_eat] && ++j == 1)
			sem_post(arg->sem_eat);
		sem_post(arg->sem_lte);
		usleep(100);
	}
	return (NULL);
}

void	philo_routine(t_philo *arg)
{
	while (get_time() <= arg->init_time)
		usleep(200);
	arg->eating_time = get_time();
	pthread_create(&arg->th, NULL, supervisor, arg);
	think(arg);
	if (arg->i % 2)
		ft_usleep(arg, arg->info[time_to_eat] / 2);
	while (1)
	{
		sem_wait(arg->sem);
		take_fork(arg);
		if (arg->info[philo_n] > 1)
		{
			eating_phase(arg);
			sem_wait(arg->sem_print);
			printf("%ld %d is sleeping\n",
				ft_interval(arg->init_time, get_time()), arg->i + 1);
			sem_post(arg->sem_print);
			ft_usleep(arg, arg->info[time_to_sleep]);
			sem_wait(arg->sem_print);
			printf("%ld %d is thinking\n",
				ft_interval(arg->init_time, get_time()), arg->i + 1);
			sem_post(arg->sem_print);
		}
	}
}

void	philos_create(t_philo *philo)
{
	int	pid;
	int	i;

	philo->i = -1;
	philo->is_dead = 0;
	while (++philo->i < philo->info[philo_n])
	{
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
			philo_routine(philo);
		if (pid > 0)
			philo->ids[philo->i] = pid;
	}
	i = -1;
	if (philo->info[ntp_must_eat])
		while (++i < philo->info[philo_n])
			sem_wait(philo->sem_eat);
	else
		sem_wait(philo->sem_death);
	i = -1;
	while (++i < philo->info[philo_n])
		kill(philo->ids[i], SIGKILL);
}
