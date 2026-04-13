#include    "../inc/philo.h"

void ft_thread_join(pthread_t *monitor,t_data *data)
{
    int i;

    i = 0; 

    pthread_join(*monitor, NULL);
    while (i < data->nb_philo)
        pthread_join(data->philos[i++].thread, NULL); 
}

void    ft_mutex_destroy(t_data *data)
{
    int i;

    i = 0;
    while (i < data->nb_philo)
        pthread_mutex_destroy(&data->forks[i++]);
}