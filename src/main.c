/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauladrettas <pauladrettas@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:16:48 by pdrettas          #+#    #+#             */
/*   Updated: 2025/05/06 20:06:01 by pauladretta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// int main (int argc, char **argv)
// {
// 	// pthread_mutex_t mutex;
// 	t_data data;
// 	t_philo philo;

// 	// pthread_t monitor_thread;
// 	// FT/FILE: initialize structs (individual philo struct & shared data struct)
// 	if (!parse_input(argc, argv))
// 		return (1);
// 	init_structs(argc, argv, &data, &philo);
// 	init_mutex(&data, &philo);
// 	// FT/FILE: create monitor_routine
// 		// pthread_create(&monitor_thread, NULL, monitor_routine, &data);
// 	// pthread_mutex_init(&data.mutex, NULL);
// 	// pthread_mutex_init(&data.forks, NULL);
// 	if (!create_threads(&data, &philo))
// 		return (1);
// 	// pthread_join(monitor_thread, NULL); // TODO: check if correct placement
// 	// pthread_mutex_destroy(&data.mutex);
// 	destroy_mutex(&data, &philo);
// 	// pthread_mutex_destroy(&data.forks);
// 	return (0);
// }

void free_all(t_data *data, t_philo *philos)
{
	if (!data)
		free(data);
	if (!philos)
		free(philos);
}

int main (int argc, char **argv)
{
	t_data *data;
	t_philo *philos;

	data = NULL;
	philos = NULL;
	data = init_data(argc, argv);
	philos = init_philos(data);
	if (!philos || !data)
		return (free_all(data, philos), 1);
	
	// int i = 0;
	// while (i < data->number_of_philosophers)
	// {
	// 	printf("id philo = %d\n", philos[i].id);
	// 	i++;
	// }
	create_threads(data, philos);
	free_all(data, philos);
		
	return (0);
}
