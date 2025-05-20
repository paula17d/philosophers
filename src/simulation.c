/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauladrettas <pauladrettas@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 21:01:38 by pauladretta       #+#    #+#             */
/*   Updated: 2025/05/20 21:39:20 by pauladretta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*routine(void *arg);

/*

*/
bool	run_simulation(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_create(&philos[i].thread, NULL, &routine, &philos[i]) != 0)
			// create a thread (first variable) for each philo in the array (last variable)
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

void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	// only one philo bc only one philo is input in one thread creation
	philo = (t_philo *)arg;
	data = philo->data;

	if (philo->id % 2 == 0 || (philo->id == data->number_of_philosophers
			&& data->number_of_philosophers != 1))
	{
		think(philo, data);
		ft_usleep((data->time_to_eat) / 2); // so that even ones wait more (/2)
	}
	// time to die nach 30 seg
	while (is_dead(data) == false)
	{
	
		// ft_usleep(52);
		// 	if (data->meals_completed >= (data->number_of_times_each_philosopher_must_eat * data->number_of_philosophers))
		// {
		// 	data->stop_simulation = true; // also means simulation done basically
		// }
		// pthread_mutex_lock(&data->test);
		take_forks(philo, data);
		pthread_mutex_lock(&data->time);
		philo->time_since_eating = get_timestamp_in_ms(); // 20:00
			// time is updated to current time after each while iteration
		pthread_mutex_unlock(&data->time);
		eat(philo, data);      // 20:10 (DONE EATING)
			// check: if timetodie is smaller than one of the 4 actions, philo dies
		put_down_forks(philo); // 20:10
		// pthread_mutex_unlock(&data->test);
		get_sleep(philo, data); // 20:20
		think(philo, data);     // 20:40 zeitvergangen = 40 time to die = 30
	}
	return (NULL);
}
