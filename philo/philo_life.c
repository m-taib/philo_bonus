/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:28:02 by mtaib             #+#    #+#             */
/*   Updated: 2023/05/27 18:57:42 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating_phase(t_philo *arg)
{
	pthread_mutex_lock(arg->next->ptr_m);
	take_fork(arg);
	pthread_mutex_lock(arg->philo_info->lte);
	arg->last_meal = get_time();
	pthread_mutex_unlock(arg->philo_info->lte);
	eat(arg);
	if (!ft_usleep(arg, arg->philo_info->info[time_to_eat]))
	{
		pthread_mutex_unlock(arg->ptr_m);
		pthread_mutex_unlock(arg->next->ptr_m);
		return (0);
	}
	if (arg->philo_info->info[ntp_must_eat])
	{
		pthread_mutex_lock(arg->dead);
		arg->n_meals++;
		pthread_mutex_unlock(arg->dead);
	}
	pthread_mutex_unlock(arg->ptr_m);
	pthread_mutex_unlock(arg->next->ptr_m);
	return (1);
}

void	*philo_routine(void *philo)
{
	t_philo	*arg;

	arg = (t_philo *)philo;
	if (arg->id % 2)
	{
		think(arg);
		ft_usleep(philo, arg->philo_info->info[time_to_eat] / 2);
	}
	while (1)
	{
		if (!check_death(arg))
			return (0);
		pthread_mutex_lock(arg->ptr_m);
		take_fork(arg);
		if (arg->philo_info->info[philo_n] == 1)
			usleep(arg->philo_info->info[time_to_die] * 1000);
		if (arg->philo_info->info[philo_n] > 1)
		{
			if (!eating_phase(arg))
				return (0);
			ft_sleep(arg);
			think(arg);
		}
	}
	return (NULL);
}

int	check_state(t_philo *philo)
{
	pthread_mutex_lock(philo->philo_info->lte);
	if ((ft_interval(philo->last_meal,
				get_time()) >= philo->philo_info->info[time_to_die])
		|| is_full(philo))
	{
		if (!is_full(philo))
		{
			pthread_mutex_lock(philo->write);
			printf("%ld %d died\n",
				ft_interval(philo->philo_info->init_time, get_time()),
				philo->id);
		}
		pthread_mutex_lock(philo->dead);
		philo->philo_info->is_dead = 1;
		pthread_mutex_unlock(philo->dead);
		if (is_full(philo))
			pthread_mutex_lock(philo->write);
		pthread_mutex_unlock(philo->write);
		pthread_mutex_unlock(philo->philo_info->lte);
		return (0);
	}
	return (1);
}

void	supervisor(t_philo *philo)
{
	t_philo	*tmp;

	tmp = philo;
	while (tmp)
	{
		if (!check_state(tmp))
		{
			pthread_mutex_unlock(philo->philo_info->lte);
			return ;
		}
		pthread_mutex_unlock(philo->philo_info->lte);
		tmp = tmp->next;
		usleep(100);
	}
}

void	philos_create(t_philo *philos)
{
	int		i;
	t_philo	*tmp;

	tmp = philos;
	i = 0;
	while (philos)
	{
		philos->id = i + 1;
		philos->last_meal = get_time();
		if (pthread_create(&philos->philo_info->ptr_t[i], NULL, philo_routine,
				philos))
		{
			ft_clear(tmp);
			return ;
		}
		philos = philos->next;
		if (philos == tmp)
			break ;
		i++;
	}
	supervisor(tmp);
	i = -1;
	while (++i < philos->philo_info->info[philo_n])
		pthread_join(philos->ptr_t[i], NULL);
	ft_clear(tmp);
}
