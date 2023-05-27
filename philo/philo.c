/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 09:47:34 by mtaib             #+#    #+#             */
/*   Updated: 2023/05/27 18:41:49 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_clear(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->philo_info->info[philo_n])
		pthread_mutex_destroy(&(philo->ptr_m[i]));
	pthread_mutex_destroy(philo->write);
	pthread_mutex_destroy(philo->dead);
	pthread_mutex_destroy(philo->philo_info->lte);
	free(philo->ptr_t);
	free(philo->ptr_m);
	free(philo->dead);
	free(philo->write);
	free(philo->philo_info->lte);
	free(philo->philo_info->info);
	free(philo->philo_info);
	ft_lstclear(&philo);
	free(philo);
}

int	main(int ac, char **av)
{
	t_info	*infos;
	t_philo	*philos;

	philos = NULL;
	if (ac < 5 || ac > 6)
		return (1);
	infos = malloc(sizeof(t_info));
	if (!infos)
		return (1);
	if (!check_args(&av[1], 6, infos))
	{
		printf("Invalid input\n");
		return (free(infos), 1);
	}
	if (!init(infos, &philos))
		return (free(infos->info), free(infos), 1);
	philos_create(philos);
	return (0);
}
