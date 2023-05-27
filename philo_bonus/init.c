/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 21:48:19 by mtaib             #+#    #+#             */
/*   Updated: 2023/05/27 15:49:10 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init(t_philo *philo)
{
	philo->ids = malloc(sizeof(int) * philo->info[philo_n]);
	if (!philo->ids)
		return (0);
	sem_unlink("/FORKS");
	sem_unlink("/EAT");
	sem_unlink("/DEATH");
	sem_unlink("/LTE");
	sem_unlink("/PRINT");
	philo->sem = sem_open("/FORKS", O_CREAT | O_EXCL, 0644,
			philo->info[philo_n]);
	philo->sem_eat = sem_open("/EAT", O_CREAT | O_EXCL, 0644, 0);
	philo->sem_death = sem_open("/DEATH", O_CREAT | O_EXCL, 0644, 0);
	philo->sem_lte = sem_open("/LTE", O_CREAT | O_EXCL, 0644, 1);
	philo->sem_print = sem_open("/PRINT", O_CREAT | O_EXCL, 0644, 1);
	philo->init_time = get_time() + 300;
	philo->is_dead = 0;
	return (1);
}
