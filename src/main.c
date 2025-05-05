/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:16:48 by pdrettas          #+#    #+#             */
/*   Updated: 2025/05/05 19:40:58 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int main (int argc, char **argv)
{
	// pthread_mutex_t mutex;
	t_data data;
	t_philo philo;

	// pthread_t monitor_thread;
	// FT/FILE: initialize structs (individual philo struct & shared data struct)
	if (!parse_input(argc, argv))
		return (1);
	init_structs(argc, argv, &data, &philo);
	init_mutex(&data, &philo);
	// FT/FILE: create monitor_routine
		// pthread_create(&monitor_thread, NULL, monitor_routine, &data);
	// pthread_mutex_init(&data.mutex, NULL);
	// pthread_mutex_init(&data.forks, NULL);
	if (!create_threads(&data, &philo))
		return (1);
	// pthread_join(monitor_thread, NULL); // TODO: check if correct placement
	// pthread_mutex_destroy(&data.mutex);
	destroy_mutex(&data, &philo);
	// pthread_mutex_destroy(&data.forks);
	return (0);
}


/*
note: get number of forks from number of philosophers (arg)
*/