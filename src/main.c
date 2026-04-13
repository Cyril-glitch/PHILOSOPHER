#include "../inc/philo.h"

int main(int ac, char **av)
{
    t_data  *data;
    pthread_t   *monitor;

    if (ac < 6)
        return (ft_putstr_fd(B_L_RED "ARGUMENTS MISSING\n" RESET, 2), 1); 
    if (!ft_init_simulation(ac, av, &data))
        return 1;
    //ft_data_display(data);
    monitor = ft_monitoring(data);
    ft_thread_join(monitor,data);
    ft_mutex_destroy(data);

    return 0;
}