#include    "../inc/philo.h"

void ft_thread_join(t_data *data)
{
    int i;

    i = 0; 
    if (data->monitor)
        pthread_join(data->monitor, NULL);
    while (i < data->nb_philo)
    {
        if (data->philo[i].thread)
            pthread_join(data->philo[i].thread, NULL); 
        i++;
    }
}

void    ft_mutex_destroy(t_data *data, int n_thrd,int to_del)
{
    int i;

    i = 0;
    while (i < n_thrd)
    {
        pthread_mutex_destroy(&data->forks[i]);
        i++;
    }
    if (to_del > 0)
        pthread_mutex_destroy(&data->stop_mutex);
    if (to_del > 1)
        pthread_mutex_destroy(&data->print_mutex);
    if (to_del > 2)
        pthread_mutex_destroy(&data->meal_mutex);
}

void    ft_clean_exit(t_data *data)
{
    if (!data)
        return ;
    ft_thread_join(data);
    ft_mutex_destroy(data, data->nb_philo,3);
    if (data->forks)
        free(data->forks);
    if (data->philo)
        free(data->philo);
    free(data);
}