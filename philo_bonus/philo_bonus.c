/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 15:54:31 by mtaib             #+#    #+#             */
/*   Updated: 2023/05/27 18:41:27 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo		*philo;

	if (ac < 5 || ac > 6)
		return (1);
	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (1);
	if (!check_args(&av[1], 6, philo))
	{
		printf("Invalid input\n");
		return (free(philo), 1);
	}
	if (!init(philo))
		return (free(philo), 1);
	philos_create(philo);
	ft_close(philo);
}
