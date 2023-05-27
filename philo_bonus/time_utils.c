/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 16:13:16 by mtaib             #+#    #+#             */
/*   Updated: 2023/05/27 16:13:27 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	curr_time;

	gettimeofday(&curr_time, NULL);
	return (curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000);
}

long	ft_interval(time_t before, time_t after)
{
	return (after - before);
}

void	ft_usleep(t_philo *vars, int time)
{
	time_t	waiting_until;

	(void)vars;
	waiting_until = get_time() + (long)time;
	while (waiting_until > get_time())
		usleep(200);
}
