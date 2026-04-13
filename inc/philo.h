#ifndef PHILO_H
# define PHILO_H

# include "../inc/colors.h"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	int						nb_philo;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						must_eat;

	long					start_time;

	volatile __sig_atomic_t	stop;

	pthread_mutex_t			stop_mutex;
	pthread_mutex_t			print_mutex;

	pthread_mutex_t			*forks;

	struct s_philo			*philos;

}							t_data;

typedef struct s_philo
{
	int						id;
	pthread_t				thread;

	long					last_meal;
	int						meals_eaten;

	pthread_mutex_t			*left_fork;
	pthread_mutex_t			*right_fork;

	t_data					*data;

}							t_philo;

//INIT
int							ft_init_simulation(int ac, char **av, t_data **data);

//UTILS
int							ft_isdigit(int c);
int							ft_isspace(int c);
int							ft_atoi(const char *nptr);
int							ft_isfull_dig(char *s);

//UTILS_2
int							ft_strlen(char *s);
void						ft_putstr_fd(char *s, int fd);
void    					ft_display_logs(t_philo *philo,int  time,char *logs);

//ROUTINE
void	*ft_routine(void *args);

//MONITORING
void    ft_data_display(t_data *data);
pthread_t	*ft_monitoring(t_data *data);

//CLEANING


void ft_thread_join(pthread_t *monitor,t_data *data);
void    ft_mutex_destroy(t_data *data);

#endif