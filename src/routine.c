#include "../inc/philo.h"

void *ft_routine(void *args)
{
    t_philo *cur_philo;

    cur_philo = (t_philo*)args; 

    pthread_mutex_lock(&cur_philo->data->print_mutex);
    printf("helloworld!\n");
    pthread_mutex_unlock(&cur_philo->data->print_mutex);

    return (NULL);
}