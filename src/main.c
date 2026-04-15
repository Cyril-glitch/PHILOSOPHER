#include "../inc/philo.h"

int main(int ac, char **av)
{
    t_data  *data;

    if (ac < 5 || ac > 6)
        return (ft_putstr_fd(BL_RED "WRONG NUMBER OF ARGUMENTS\n" RESET, 2), 1); 
    if (!ft_init_simulation(ac, av, &data))
        return 1;
    ft_start_simulation(data);
    //ft_data_display(data);
    ft_monitoring(data);
    ft_thread_join(data);
    ft_mutex_destroy(data);

    return 0;
}