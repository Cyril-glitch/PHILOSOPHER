#include "../inc/philo.h"

long	ft_gettime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_usec / 1000) + (tv.tv_sec * 1000));
}

long	ft_duration(long last_time)
{
	return (ft_gettime() - last_time);
}

int    ft_display_logs(t_philo *philo,long  time,char *logs)
{
	if (ft_isfinish(philo))
		return 0;
    pthread_mutex_lock(&philo->data->print_mutex);
    printf("%ld %d %s\n",time, philo->id, logs);
    pthread_mutex_unlock(&philo->data->print_mutex);
    return 1;
}

void    ft_display_end(t_philo *philo,long  time,char *logs)
{
    pthread_mutex_lock(&philo->data->print_mutex);
    printf("%ld %d %s\n",time, philo->id, logs);
    pthread_mutex_unlock(&philo->data->print_mutex);
}

void    ft_waiting(long pause,t_philo *cur_philo)
{
    long    start;

    start = ft_gettime();
    while (ft_duration(start) < (pause))
    {
        usleep(1);
        if (ft_isfinish(cur_philo))
            return ;
    }
}