/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:16:48 by pdrettas          #+#    #+#             */
/*   Updated: 2025/05/23 17:30:51 by pdrettas         ###   ########.fr       */
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

	data = NULL;
	philos = NULL;
	if (!parse_input(argc, argv))
		return (1);
	data = init_data(argc, argv);
	philos = init_philos(data);
	if (!philos || !data)
		return (free_all(data, philos, argv), 1);
	run_simulation(data, philos);
	free_all(data, philos, argv);
	return (0);
}
