/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauladrettas <pauladrettas@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 21:01:38 by pauladretta       #+#    #+#             */
/*   Updated: 2025/05/22 20:29:00 by pauladretta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/*
create a new thread for each philo, 
have it run the routine() function, passing it a pointer to philos[i]. 
-> if thread fails to be created, return false.
after creation, check if any philo dies.
wait for all threads to finish
-> if thread fails to be joined, return false.
*/
bool	run_simulation(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_create(&philos[i].thread, NULL, &routine, &philos[i]) != 0)
			return (false);
		i++;
	}
	monitor_all_philos(philos, data);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
			return (false);
		i++;
	}
	return (true);
}
