#include "philo.h"

void	*supervisor(void *philo)
{
	t_philo *arg;
	int	i;
	int	j = 0;

	i = -1;	
	arg = (t_philo *)philo;
	while (1)
	{
		sem_wait(arg->sem_lte);
		// diff = lksdf
		// sem_post();
		if (ft_interval(arg->eating_time,
				get_time()) >= arg->info[time_to_die])
		{
			i++;
			if (!i)
			{
				i = -1;
				sem_wait(arg->sem_print);
				printf("%ld %d died\n",
					ft_interval(arg->init_time, get_time()), arg->i + 1);
				arg->is_dead = 1;
				while (++i < arg->info[philo_n])
					sem_post(arg->sem_eat);
				sem_post(arg->sem_death);
				//exit(1);
			}
		}
		sem_post(arg->sem_lte);
		//sem_wait(arg->sem_lte);
		//has_eaten_enough = 
		//sem_post
		if (arg->info[ntp_must_eat] && arg->nb_to_eat == arg->info[ntp_must_eat] && ++j == 1)
			sem_post(arg->sem_eat);
		usleep(200);
	}
	return (NULL);

}

void    philo_routine(t_philo *arg)
{
	int	i;
	int	j;

	j = -1;	
	i = arg->i;
	while(get_time() <= arg->init_time)
		usleep(200);

	arg->eating_time = get_time();
	pthread_create(&arg->th, NULL, supervisor, arg);
	sem_wait(arg->sem_print);
	printf("%ld %d is thinking\n",
		ft_interval(arg->init_time, get_time()), i + 1);
	sem_post(arg->sem_print);	
	if (i % 2)//just for the first time
			usleep(arg->info[time_to_eat] * 500);
	while (1)
	{
		sem_wait(arg->sem);
		
		sem_wait(arg->sem_print);
		printf("%ld %d has taken a fork\n",
			ft_interval(arg->init_time, get_time()), i + 1);
		sem_post(arg->sem_print);
		
		if (arg->info[philo_n] > 1)
		{
			sem_wait(arg->sem);
			
			sem_wait(arg->sem_print);
			printf("%ld %d has taken a fork\n",
				ft_interval(arg->init_time, get_time()), i + 1);
			sem_post(arg->sem_print);
			
			sem_wait(arg->sem_lte);
			arg->eating_time = get_time();
			sem_post(arg->sem_lte);

			sem_wait(arg->sem_print);
			printf("%ld %d is eating\n",
				ft_interval(arg->init_time, get_time()), i + 1);
			//get time and pass it to ft_usleep
			sem_post(arg->sem_print);
			
			if (!ft_usleep(arg, arg->info[time_to_eat]))
				return ;
			sem_wait(arg->sem_lte);
			if (arg->info[ntp_must_eat])
				arg->nb_to_eat++;
			sem_post(arg->sem_lte);
			//usleep(arg->info[time_to_eat] * 1000);
			sem_post(arg->sem);
			sem_post(arg->sem);
			
			sem_wait(arg->sem_print);
			printf("%ld %d is sleeping\n",
				ft_interval(arg->init_time, get_time()), i + 1);
			sem_post(arg->sem_print);
			
			ft_usleep(arg, arg->info[time_to_sleep]);
			//usleep(arg->info[time_to_sleep] * 1000);
		}	
		sem_wait(arg->sem_print);
		printf("%ld %d is thinking\n",
			ft_interval(arg->init_time, get_time()), i + 1);
		sem_post(arg->sem_print);	
	}
}

void	philos_create(t_philo *philo)
{
	int	pid;
	int	i;

	sem_unlink("/FORKS");
	sem_unlink("/EAT");
	sem_unlink("/DEATH");
	sem_unlink("/LTE");
	sem_unlink("/PRINT");
	philo->sem = sem_open("/FORKS", O_CREAT | O_EXCL, 0644, philo->info[philo_n]);
	philo->sem_eat = sem_open("/EAT", O_CREAT | O_EXCL, 0644, 0);
	philo->sem_death = sem_open("/DEATH", O_CREAT | O_EXCL, 0644, 0);
	philo->sem_lte = sem_open("/LTE", O_CREAT | O_EXCL, 0644, 1);
	philo->sem_print = sem_open("/PRINT", O_CREAT | O_EXCL, 0644, 1);
	philo->init_time = get_time() + 300;
	philo->i = -1;
	philo->is_dead = 0;
	while (++philo->i < philo->info[philo_n])
	{
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
			philo_routine(philo);
		if (pid > 0)
			philo->ids[philo->i] = pid;
	}
	i = -1;
	if (philo->info[ntp_must_eat])
	{
		while (++i < philo->info[philo_n])
			sem_wait(philo->sem_eat);
	}
	else
		sem_wait(philo->sem_death);

	i = -1;
	while (++i < philo->info[philo_n])
		kill(philo->ids[i], 15);
}
int	main(int ac, char **av)
{
	t_philo *philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (0);
	if (ac < 5 || ac > 6)
		return (1);
	if (!check_args(&av[1], ac, philo))
		return (free(philo),1);
	philo->nb_to_eat = 0;
	philo->info[ntp_must_eat] = 0;
	if (ac == 6 && is_num(&av[5]) && (ft_atoi(av[5]) > 0))
		philo->info[ntp_must_eat] = ft_atoi(av[5]);
	philos_create(philo);
}

