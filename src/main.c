/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauladrettas <pauladrettas@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:16:48 by pdrettas          #+#    #+#             */
/*   Updated: 2025/05/20 21:16:30 by pauladretta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/*
parse input and initialize all structs from header file.
-> in case of initialization failure free everything.
runs the full philosophers simulation.
free everything.
*/ 
int	main(int argc, char **argv)
{
	t_data	*data;
	t_philo	*philos;

	// set to NULL in case of free_all (variables need to have value)
	data = NULL;
	philos = NULL;
	if (!parse_input(argc, argv))
		return (1);
	data = init_data(argc, argv);
	philos = init_philos(data);
	if (!philos || !data)
		return (free_all(data, philos, argv), 1);
	// int i = 0;
	// while (i < data->number_of_philosophers)
	// {
	// 	printf("id philo = %d\n", philos[i].id);
	// 	i++;
	// }
	run_simulation(data, philos); // formerly create_threads
	free_all(data, philos, argv);
	return (0);
}
