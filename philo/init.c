/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 20:11:53 by mtaib             #+#    #+#             */
/*   Updated: 2023/05/22 16:33:57 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*ft_new_philo()
{
	t_philo *new;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (0);
	new->n_meals = 0;
	new->last_meal = 0;
	new->next = 0;
	return (new);
}

void	ft_add_back(t_philo **philos, t_philo *newphilo)
{
	t_philo *tmp;
	tmp = *philos;
	
	if (!*philos)
	{
		*philos = newphilo;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = newphilo;
}

void	create_philos_list(t_philo **philos, int n)
{
	int		i;
	t_philo *tmp;

	i = -1;
	while (++i < n)
		ft_add_back(philos, ft_new_philo());
	tmp = *philos;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = *philos;
}

int	init(t_info *infos, t_philo **philos)
{
	int	i;
	int	j;
	t_philo *tmp;
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
	pthread_mutex_init(infos->write, NULL);
	pthread_mutex_init(infos->dead, NULL);
	pthread_mutex_init(infos->lte, NULL);
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
	return (1);
}

