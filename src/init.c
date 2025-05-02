/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:16:41 by pdrettas          #+#    #+#             */
/*   Updated: 2025/05/02 20:21:54 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void init_structs(int argc, char **argv, t_data *data, t_philo *philo)
{	
	(void) argc;
	
	// PHILO STRUCT
	philo->ID = 0;
	philo->data = data;
	philo->left_fork = 0;
	philo->right_fork = 0;
	
	// DATA STRUCT
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		data->number_of_times_each_philosopher_must_eat = -1; // use later in ft
} // TODO: return value

bool create_threads(t_data *data, t_philo *philo)
{
	int n;
	
	n = 1;
	while (n <= data->number_of_philosophers)
	{
		if (pthread_create(&philo->thread_philo[n], NULL, &routine, &philo) != 0)
			return (false);
		philo->ID++;
		// printf("id = %d\n", philo->ID);
		n++;
	}
	n = 1;
	while (n <= data->number_of_philosophers)
	{
		if (pthread_join(philo->thread_philo[n], NULL) != 0)
			return (false); 
		n++;
	}

	return (true);
}
