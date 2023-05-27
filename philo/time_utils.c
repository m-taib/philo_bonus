/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 09:48:16 by mtaib             #+#    #+#             */
/*   Updated: 2023/05/27 18:55:28 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	curr_time;

	gettimeofday(&curr_time, NULL);
	return ((curr_time.tv_sec * 1000) + (curr_time.tv_usec / 1000));
}

long	ft_interval(time_t before, time_t after)
{
	return (after - before);
}

int	ft_usleep(t_philo *vars, int time)
{
	time_t	waiting_until;

	waiting_until = get_time() + (long)time;
	while (waiting_until > get_time())
	{
		pthread_mutex_lock(vars->dead);
		if (vars->philo_info->is_dead)
		{
			pthread_mutex_unlock(vars->dead);
			return (0);
		}
		pthread_mutex_unlock(vars->dead);
		usleep(100);
	}
	return (1);
}
