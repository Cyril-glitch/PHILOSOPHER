#include "../inc/philo.h"

int main(int ac, char **av)
{
    t_data  *data;

    if (ac < 6)
        return (ft_putstr_fd(B_L_RED "ARGUMENTS MISSING\n" RESET, 2), 1); 
    if (!ft_init_data(ac, av, &data))
        return 1;
    ft_data_display(data);
    ft_thread_join(data);
    ft_mutex_destroy(data);

    return 0;
}