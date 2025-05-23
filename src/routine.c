/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:26:26 by pauladretta       #+#    #+#             */
/*   Updated: 2025/05/23 17:32:34 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/*
routine for one philosopher.
- if the philosopher has an even ID OR is the last one (and not alone),
  they think/wait before starting (to avoid deadlocks with forks).
- then, they loop through the routine:
  take forks → update eating time → eat → put down forks → sleep → think.
- the eating timestamp update (before meal) is protected by a mutex to prevent
  race conditions with the death monitor, which reads the same value.
- the loop continues until the simulation is stopped -> a philosopher dies.
*/
void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->id % 2 == 0 || (philo->id == data->number_of_philosophers
			&& data->number_of_philosophers != 1))
	{
		think(philo, data);
		ft_usleep((data->time_to_eat) / 2);
	}
	while (get_stop_simulation_value(data) == false)
	{
		take_forks(philo, data);
		pthread_mutex_lock(&data->time);
		philo->time_of_eating = get_timestamp_in_ms();
		pthread_mutex_unlock(&data->time);
		eat(philo, data);
		put_down_forks(philo);
		get_sleep(philo, data);
		think(philo, data);
	}
	return (NULL);
}
