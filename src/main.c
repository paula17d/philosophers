/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:16:48 by pdrettas          #+#    #+#             */
/*   Updated: 2025/04/23 19:20:58 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int main (int args, char **argv)
{
	t_data data;
	t_philo philo;
	// pthread_t monitor_thread;
	// FT/FILE: initialize structs (individual philo struct & shared data struct)
	if (!parse_input(args, argv))
		return(1);
	init_structs(args, argv, &data); // return value?
	// FT/FILE: create monitor_routine
		// pthread_create(&monitor_thread, NULL, monitor_routine, &data);
	// FT/FILE: thread creation for each philo (w input of routine --> routine FT)
		// routine: even philos start w right fork. uneven w left fork (prevents deadlocks by avoiding circular waiting)
	// pthread_join(monitor_thread, NULL); // TODO: check if correct placement
	return (0);
}


/*
note: get number of forks from number of philosophers (arg)
*/