#ifndef PHILO_H
#   define PHILO_H

# include "../libft/inc/libft.h"
# include "../libft/inc/ft_printf.h"
# include "../libft/inc/colors.h"
# include <pthread.h>

typedef struct s_data
{
    int                 nb_philo;
    int                 time_to_die;
    int                 time_to_eat;
    int                 time_to_sleep;
    int                 must_eat;

    long                start_time;

    volatile __sig_atomic_t               stop;

    pthread_mutex_t     stop_mutex;
    pthread_mutex_t     print_mutex;

    pthread_mutex_t     *forks;

    struct s_philo      *philos;

}   t_data;

typedef struct s_philo
{
    int             id;
    pthread_t       thread;

    long            last_meal;
    int             meals_eaten;

    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;

    t_data          *data;

}   t_philo;


int    ft_init_data(int ac,char **av, t_data **data);



#endif