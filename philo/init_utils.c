/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:10:32 by mtaib             #+#    #+#             */
/*   Updated: 2023/05/27 19:20:46 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*ft_new_philo(void)
{
	t_philo	*new;

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
	t_philo	*tmp;

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

void	destroy_check(t_info *infos, int i)
{
	int	j;

	j = -1;
	if (i == 4 || i == 2 || i == 3)
		while (++j < infos->info[philo_n])
			pthread_mutex_destroy(&(infos->ptr_m[j]));
	if (i == 2 || i == 3)
		pthread_mutex_destroy(infos->write);
	if (i == 3)
		pthread_mutex_destroy(infos->dead);
}

void	ft_lstclear(t_philo **lst)
{
	t_philo	*tmp;
	t_philo	*first_node;

	first_node = *lst;
	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		if (first_node == tmp)
			break ;
		free(*lst);
		(*lst) = tmp;
	}
}

void	free_mutexes(t_info *infos)
{
	free(infos->ptr_t);
	free(infos->ptr_m);
	free(infos->dead);
	free(infos->write);
	free(infos->lte);
}
