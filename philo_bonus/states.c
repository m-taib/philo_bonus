/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 11:26:37 by mtaib             #+#    #+#             */
/*   Updated: 2023/05/27 16:11:01 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philo *arg)
{
	sem_wait(arg->sem_print);
	printf("%ld %d is thinking\n",
		ft_interval(arg->init_time, get_time()),
		arg->i + 1);
	sem_post(arg->sem_print);
}

void	take_fork(t_philo *arg)
{
	sem_wait(arg->sem_print);
	printf("%ld %d has taken a fork\n",
		ft_interval(arg->init_time, get_time()),
		arg->i + 1);
	sem_post(arg->sem_print);
}

void	eat(t_philo *arg)
{
	sem_wait(arg->sem_print);
	printf("%ld %d is eating\n",
		ft_interval(arg->init_time, get_time()),
		arg->i + 1);
	sem_post(arg->sem_print);
}

void	ft_sleep(t_philo *arg)
{
	sem_wait(arg->sem_print);
	printf("%ld %d is sleeping\n",
		ft_interval(arg->init_time, get_time()),
		arg->i + 1);
	sem_post(arg->sem_print);
}

void	eating_phase(t_philo *arg)
{
	sem_wait(arg->sem);
	take_fork(arg);
	sem_wait(arg->sem_lte);
	arg->eating_time = get_time();
	sem_post(arg->sem_lte);
	eat(arg);
	ft_usleep(arg, arg->info[time_to_eat]);
	sem_wait(arg->sem_lte);
	if (arg->info[ntp_must_eat])
		arg->nb_to_eat++;
	sem_post(arg->sem_lte);
	sem_post(arg->sem);
	sem_post(arg->sem);
}
