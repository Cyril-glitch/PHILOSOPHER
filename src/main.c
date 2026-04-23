/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 11:37:33 by cycolonn          #+#    #+#             */
/*   Updated: 2026/04/23 11:42:23 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac < 5 || ac > 6)
		return (ft_putstr_fd(BL_RED "WRONG NUMBER OF ARGUMENTS\n" RESET, 2), 1);
	if (!ft_init_simulation(ac, av, &data))
		return (1);
	if (!ft_start_simulation(data))
		return (1);
	if (!ft_monitoring(data))
		return (1);
	ft_clean_exit(data);
	return (0);
}
