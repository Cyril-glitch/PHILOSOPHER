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
	pthread_mutex_t			meal_mutex;

	pthread_mutex_t			*forks;

	struct s_philo			*philo;

	pthread_t				monitor;

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
void						ft_start_simulation(t_data *data);
long						ft_gettime(void);

//UTILS

int							ft_strlen(char *s);
void						ft_putstr_fd(char *s, int fd);
int							ft_isdigit(int c);
int							ft_isspace(int c);
int							ft_isfull_dig(char *s);
int							ft_atoi(const char *nptr);

//timelogs
int    						ft_display_logs(t_philo *philo,long  time,char *logs);
void    					ft_display_end(t_philo *philo,long  time,char *logs);
long						ft_duration(long last_time);
void    					ft_waiting(long pause,t_philo *cur_philo);

//ROUTINE
int		ft_isfinish(t_philo *cur_philo);
void	*ft_routine(void *args);

//ACTIONS
int		ft_left_fork(t_philo *cur_philo);
int		ft_right_fork(t_philo *cur_philo);
void	ft_meal(t_philo *cur_philo);
void	ft_sleep(t_philo *cur_philo);
void	ft_think(t_philo *cur_philo);

//MONITORING
//void	ft_data_display(t_data *data);
void	ft_monitoring(t_data *data);

//CLEANING
void 	ft_thread_join(t_data *data);
void    ft_mutex_destroy(t_data *data);

#endif