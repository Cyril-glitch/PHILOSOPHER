#include "../inc/philo.h"

long	ft_gettime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_usec / 1000) + (tv.tv_sec * 1000));
}

long	ft_timer(long start_time)
{
	return (ft_gettime() - start_time);
}

void    ft_display_logs(t_philo *philo,long  time,char *logs)
{
    pthread_mutex_lock(&philo->data->print_mutex);
    printf("%d %ld %s\n", philo->id, time, logs);
    pthread_mutex_unlock(&philo->data->print_mutex);
}