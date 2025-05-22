/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauladrettas <pauladrettas@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:28:33 by pauladretta       #+#    #+#             */
/*   Updated: 2025/05/22 20:48:09 by pauladretta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/*
prints a status message for a philosopher with a timestamp.
- uses mutex to protect values of meals_completed, stop_simulation, and printf.
- tracks meals_completed if a philo is eating until meal limit is reached.
- if all meals are completed, sets stop_simulation to true.
- only prints if simulation is still running.
*/
void	print_message(char *msg, t_philo *philo, t_data *data)
{
	long	time_since_start_simulation;
	time_since_start_simulation = get_timestamp_in_ms() - data->start_time;
	
	pthread_mutex_lock(&data->print);
	if (ft_strcmp(msg, "is eating") == 0 && data->stop_simulation == false && data->number_of_times_each_philosopher_must_eat != -1)
	{
		data->meals_completed++;
	}
	// if (data->meals_completed > (data->number_of_times_each_philosopher_must_eat
	// 		* data->number_of_philosophers) && data->number_of_times_each_philosopher_must_eat != -1)
	// {
	// 	data->stop_simulation = true;
    //     printf("%lu %d %s\n", time_since_start_simulation, philo->id, msg);
	// }
	if (data->stop_simulation == false)
	{
		printf("%lu %d %s\n", time_since_start_simulation, philo->id, msg);
	}
	pthread_mutex_unlock(&data->print);
}
