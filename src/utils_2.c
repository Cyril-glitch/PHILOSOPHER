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

void    ft_display_logs(t_philo *philo,long  time,char *logs)
{
    pthread_mutex_lock(&philo->data->print_mutex);
    printf("%d %ld %s\n", philo->id, time, logs);
    pthread_mutex_unlock(&philo->data->print_mutex);
}