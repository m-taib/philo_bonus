/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 09:47:58 by mtaib             #+#    #+#             */
/*   Updated: 2023/05/27 18:36:05 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

long	ft_atoi(char *str);
int		check_args(char **av, int ac, t_info *philo);

int	is_num(char **av)
{
	int	i;
	int	j;

	j = 0;
	i = -1;
	while (av[++i])
	{
		j = -1;
		while (av[i][++j])
		{
			while (av[i][j] && av[i][j] == ' ')
				j++;
			if (av[i][j] == '+' || av[i][j] == '-')
				j++;
			if (!(av[i][j] >= '0' && av[i][j] <= '9'))
				return (0);
		}
	}
	return (1);
}

int	check_args(char **av, int ac, t_info *philo)
{
	int		i;
	long	*args;

	if (!is_num(av))
		return (0);
	args = malloc(sizeof(long) * (ac - 1));
	if (!args)
		return (0);
	memset(args, 0, sizeof(long) * (ac - 1));
	i = 0;
	while (av[i])
		i++;
	if (i == 5)
		args[i] = 0;
	i = -1;
	while (av[++i])
		args[i] = ft_atoi(av[i]);
	i = -1;
	while (av[++i])
	{
		if (args[i] <= 0 || args[i] > INT_MAX || args[i] < INT_MIN)
			return (free(args), 0);
	}
	philo->info = args;
	return (1);
}

long	ft_atoi(char *str)
{
	int		i;
	long	arb;
	long	res;

	arb = 1;
	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\n' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\t' || str[i] == '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			arb *= -1;
	res = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res * arb);
}

int	is_full(t_philo *philo)
{
	t_philo	*tmp;

	tmp = philo;
	if (!philo->philo_info->info[ntp_must_eat])
		return (0);
	while (philo)
	{
		pthread_mutex_lock(philo->dead);
		if (philo->n_meals < philo->philo_info->info[ntp_must_eat])
		{
			pthread_mutex_unlock(philo->dead);
			return (0);
		}
		pthread_mutex_unlock(philo->dead);
		philo = philo->next;
		if (tmp == philo)
			break ;
	}
	return (1);
}

int	check_death(t_philo *arg)
{
	pthread_mutex_lock(arg->dead);
	if (arg->philo_info->is_dead)
	{
		pthread_mutex_unlock(arg->dead);
		return (0);
	}
	pthread_mutex_unlock(arg->dead);
	return (1);
}
