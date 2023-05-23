#include "philo.h"

int	main(int ac, char **av)
{
	t_info *infos;
	t_philo *philos;

	philos = NULL;
	if (ac < 5 || ac > 6)
		return (1);
	infos = malloc(sizeof(t_info));
	if (!infos)
		return (0);
	if (!check_args(&av[1], ac, infos))
		return (free(infos),1);
	if (!init(infos, &philos))
	{
		//if (infos->nb_to_eat)
		//	free(infos->nb_to_eat);
		return (free(infos->info), free(infos) ,1);
	}
	philos_create(philos);
	return (0);
}
