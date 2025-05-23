/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 21:05:41 by pauladretta       #+#    #+#             */
/*   Updated: 2025/05/23 17:30:11 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/*
goes through an infinite loop of all philosophers checking
if their death occurred through the death_monitor.
*/
bool	monitor_all_philos(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	while (1)
	{
		if (death_monitor(&philos[i], data) == true)
		{
			return (true);
		}
		i++;
		if (i == data->number_of_philosophers)
			i = 0;
	}
}

/*
checks if a philosopher died by:
- calculating time since last meal.
- if time exceeds time_to_die, prints death message, releases forks,
and stops the simulation.
- uses mutexes to protect shared data and avoid race conditions.
*/
bool	death_monitor(t_philo *philo, t_data *data)
{
	long	time_since_start_simulation;
	long	current_time_lived_philo;

	time_since_start_simulation = get_timestamp_in_ms() - data->start_time;
	pthread_mutex_lock(&data->time);
	current_time_lived_philo = get_timestamp_in_ms() - philo->time_of_eating;
	pthread_mutex_unlock(&data->time);
	pthread_mutex_lock(&data->print);
	if (data->stop_simulation == true)
	{
		pthread_mutex_unlock(&data->print);
		return (true);
	}
	if (current_time_lived_philo > data->time_to_die)
	{
		data->stop_simulation = true;
		put_down_forks(philo);
		printf("%lu %d died\n", time_since_start_simulation, philo->id);
		pthread_mutex_unlock(&data->print);
		return (true);
	}
	pthread_mutex_unlock(&data->print);
	return (false);
}

// first if check how many meals have been eaten
bool	get_stop_simulation_value(t_data *data)
{
	pthread_mutex_lock(&data->print);
	if (data->meals_completed > (data->number_of_times_each_philosopher_must_eat
			* data->number_of_philosophers)
		&& data->number_of_times_each_philosopher_must_eat != -1)
	{
		data->stop_simulation = true;
	}
	if (data->stop_simulation == false)
	{
		pthread_mutex_unlock(&data->print);
		return (false);
	}
	else
	{
		pthread_mutex_unlock(&data->print);
		return (true);
	}
}
