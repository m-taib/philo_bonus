#include "philo.h"

long	get_time(void)
{
	struct timeval curr_time;

	gettimeofday(&curr_time, NULL);
	return (curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000);
}

long	ft_interval(time_t before, time_t after)
{
	return (after - before);
}

void	ft_usleep(t_philo *vars, int time)
{
	/*time_t	waiting_until;
	(void)vars;
	waiting_until = get_time() + time;
	while (waiting_until >= get_time())
		usleep(200);*/
	struct timeval	t1;
	struct timeval	t2;
	long long	diff;
	
	gettimeofday(&t1, NULL);
	(void)vars;
	time = time * 1000;
	while (1)
	{
		gettimeofday(&t2, NULL);
		diff = 1000000 * (t2.tv_sec - t1.tv_sec) + t2.tv_usec - t1.tv_usec;
		if (diff >= time)
			return ;
		usleep(200);
	}
}

