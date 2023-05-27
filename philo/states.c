/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 11:26:37 by mtaib             #+#    #+#             */
/*   Updated: 2023/05/26 20:24:44 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philo *arg)
{
	pthread_mutex_lock(arg->write);
	pthread_mutex_lock(arg->dead);
	if (arg->philo_info->is_dead)
	{
		pthread_mutex_unlock(arg->dead);
		pthread_mutex_unlock(arg->write);
		return ;
	}
	pthread_mutex_unlock(arg->dead);
	printf("%ld %d is thinking\n",
		ft_interval(arg->philo_info->init_time, get_time()),
		arg->id);
	pthread_mutex_lock(arg->dead);
	if (arg->philo_info->is_dead)
	{
		pthread_mutex_unlock(arg->dead);
		pthread_mutex_unlock(arg->write);
		return ;
	}
	pthread_mutex_unlock(arg->dead);
	pthread_mutex_unlock(arg->write);
}

void	take_fork(t_philo *arg)
{
	pthread_mutex_lock(arg->write);
	pthread_mutex_lock(arg->dead);
	if (arg->philo_info->is_dead)
	{
		pthread_mutex_unlock(arg->dead);
		pthread_mutex_unlock(arg->write);
		return ;
	}
	pthread_mutex_unlock(arg->dead);
	printf("%ld %d has taken a fork\n",
		ft_interval(arg->philo_info->init_time, get_time()),
		arg->id);
	pthread_mutex_lock(arg->dead);
	if (arg->philo_info->is_dead)
	{
		pthread_mutex_unlock(arg->dead);
		pthread_mutex_unlock(arg->write);
		return ;
	}
	pthread_mutex_unlock(arg->dead);
	pthread_mutex_unlock(arg->write);
}

void	eat(t_philo *arg)
{
	pthread_mutex_lock(arg->write);
	pthread_mutex_lock(arg->dead);
	if (arg->philo_info->is_dead)
	{
		pthread_mutex_unlock(arg->dead);
		pthread_mutex_unlock(arg->write);
		return ;
	}
	pthread_mutex_unlock(arg->dead);
	printf("%ld %d is eating\n",
		ft_interval(arg->philo_info->init_time, get_time()),
		arg->id);
	pthread_mutex_lock(arg->dead);
	if (arg->philo_info->is_dead)
	{
		pthread_mutex_unlock(arg->dead);
		pthread_mutex_unlock(arg->write);
		return ;
	}
	pthread_mutex_unlock(arg->dead);
	pthread_mutex_unlock(arg->write);
}

int	ft_sleep(t_philo *arg)
{
	pthread_mutex_lock(arg->write);
	pthread_mutex_lock(arg->dead);
	if (arg->philo_info->is_dead)
	{
		pthread_mutex_unlock(arg->dead);
		return (pthread_mutex_unlock(arg->write), 0);
	}
	pthread_mutex_unlock(arg->dead);
	printf("%ld %d is sleeping\n",
		ft_interval(arg->philo_info->init_time, get_time()),
		arg->id);
	pthread_mutex_lock(arg->dead);
	if (arg->philo_info->is_dead)
	{
		pthread_mutex_unlock(arg->dead);
		return (pthread_mutex_unlock(arg->write), 0);
	}
	pthread_mutex_unlock(arg->dead);
	pthread_mutex_unlock(arg->write);
	if (!ft_usleep(arg, arg->philo_info->info[time_to_sleep]))
	{
		pthread_mutex_unlock(arg->next->ptr_m);
		return (pthread_mutex_unlock(arg->ptr_m), 0);
	}
	return (1);
}
