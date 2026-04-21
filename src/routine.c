#include "../inc/philo.h"

static void	ft_anti_queue(t_philo *cur_philo)
{
	if ((cur_philo->id & 1) && cur_philo->data->nb_philo > 1)
		ft_waiting(cur_philo->data->time_to_eat / 2, cur_philo);
}

int	ft_isfinish(t_philo *cur_philo)
{
	pthread_mutex_lock(&cur_philo->data->stop_mutex);
	if (cur_philo->data->stop == 1)
	{
		pthread_mutex_unlock(&cur_philo->data->stop_mutex);
		return (1);
	}
	pthread_mutex_unlock(&cur_philo->data->stop_mutex);
	return (0);
}

void	*ft_routine(void *args)
{
	t_philo *cur_philo;

	cur_philo = (t_philo *)args;
	ft_start_line(cur_philo->data->start_time);
	ft_anti_queue(cur_philo);
	while (1)
	{
		if (ft_isfinish(cur_philo))
			return (NULL);
		ft_meal(cur_philo);
		ft_sleep(cur_philo);
		ft_think(cur_philo);
	}
	return (NULL);
}

void	*ft_solo_routine(void *args)
{
	t_philo *cur_philo;

	cur_philo = (t_philo *)args;
	ft_start_line(cur_philo->data->start_time);
	pthread_mutex_lock(cur_philo->right_fork);
	ft_display_logs(cur_philo, ft_duration(cur_philo->data->start_time),MINT "has taken right fork" RESET);
	pthread_mutex_unlock(cur_philo->right_fork);	
	return (NULL);
}

/*
1/Dans une configuration avec un nombre de Philos Pairs on peut faire manger tout les philos en deux tours.
2/Dans une configuration avec un nombre de Philos imPairs tous les philos mangent en deux tours sauf un qui devra attendre un troisieme tours.
3/Donc si le time to die ne permet pas de survivre plus de trois tour ou si les philo peuvent se retrouver en duel plus de deux fois la simulation fini  sur un mort
4/pour le time to die on ne peux rien faire mais pour le nombre de duel on a deux levier 
5/Le time to sleep permet au philo qui n'ont pas manger au 1er tour d'avoir de l'avance sur le deuxieme tour
6/Le time to think permet au philo qui n'ont pas manger au 2eme tour d'avoir de l'avance sur le troisieme tour 
7/Malhereusement si lors du 2eme tour un philo qui a manger au 1er tour se reveille il peut se retrouver en competion contre un philo qui attends le 3eme tours
8/On en conclue donc que dans une simulation impairs un philo doit rester hors jeu un tout petit peu plus que deux tours

*/