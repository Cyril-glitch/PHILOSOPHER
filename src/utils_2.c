#include "../inc/philo.h"

int ft_strlen(char *s)
{
    int i;

    i = 0;
    while(s[i])
        i++;
    return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

void    ft_display_logs(t_philo *philo,int  time,char *logs)
{
    pthread_mutex_lock(&philo->data->print_mutex);
    printf("%d %d %s\n", time, philo->id, logs);
    pthread_mutex_unlock(&philo->data->print_mutex);
}