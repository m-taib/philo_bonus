/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 20:11:53 by mtaib             #+#    #+#             */
/*   Updated: 2023/05/26 20:28:14 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_philos_list(t_philo **philos, int n)
{
	int		i;
	t_philo	*tmp;

	i = -1;
	while (++i < n)
		ft_add_back(philos, ft_new_philo());
	tmp = *philos;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = *philos;
}

void	philos_creation(t_info *infos, t_philo **philos)
{
	t_philo	*tmp;
	int		i;

	create_philos_list(philos, infos->info[philo_n]);
	tmp = *philos;
	i = 0;
	tmp->philo_info = infos;
	tmp->philo_info->is_dead = 0;
	while (tmp)
	{
		tmp->ptr_t = &infos->ptr_t[i];
		tmp->ptr_m = &infos->ptr_m[i];
		tmp->dead = infos->dead;
		tmp->write = infos->write;
		tmp->philo_info = infos;
		tmp = tmp->next;
		if (tmp == *philos)
			break ;
		i++;
	}
}

int	init_mutexes(t_info *infos)
{
	int	i;
	int	j;

	i = -1;
	while (++i < infos->info[philo_n])
	{
		if (pthread_mutex_init(&(infos->ptr_m[i]), NULL))
		{
			j = -1;
			while (++j < i)
				pthread_mutex_destroy(&(infos->ptr_m[j]));
			return (0);
		}
	}
	if (pthread_mutex_init(infos->write, NULL))
		return (4);
	if (pthread_mutex_init(infos->dead, NULL))
		return (2);
	if (pthread_mutex_init(infos->lte, NULL))
		return (3);
	return (1);
}

int	init(t_info *infos, t_philo **philos)
{
	infos->init_time = get_time();
	infos->ptr_m = malloc(infos->info[philo_n] * sizeof(pthread_mutex_t));
	if (!infos->ptr_m)
		return (0);
	infos->ptr_t = malloc(sizeof(pthread_t) * infos->info[philo_n]);
	if (!infos->ptr_t)
		return (0);
	infos->dead = malloc(sizeof(pthread_mutex_t));
	if (!infos->dead)
		return (0);
	infos->write = malloc(sizeof(pthread_mutex_t));
	if (!infos->write)
		return (0);
	infos->lte = malloc(sizeof(pthread_mutex_t));
	if (!infos->lte)
		return (0);
	if (init_mutexes(infos) == 0 || init_mutexes(infos) > 1)
	{
		destroy_check(infos, init_mutexes(infos));
		free_mutexes(infos);
		return (0);
	}
	philos_creation(infos, philos);
	return (1);
}
