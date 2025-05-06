/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauladrettas <pauladrettas@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:16:41 by pdrettas          #+#    #+#             */
/*   Updated: 2025/05/06 22:02:07 by pauladretta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// forks mutex
// void init_mutex(t_data *data, t_philo *philo)
// {
// 	int i;

// 	i = 0;
// 	while (i < data->number_of_philosophers)
// 	{
// 		pthread_mutex_init(&philo->data->forks[i], NULL);
// 		i++;
// 	}
// }

// TODO: include destroy print mutex
// void destroy_mutex(t_data *data, t_philo *philo)
// {
// 	int i;

// 	i = 0;
// 	while (i < data->number_of_philosophers)
// 	{
// 		pthread_mutex_destroy(&philo->data->forks[i]);
// 		i++;
// 	}
// }

t_data *init_data(int argc, char **argv)
{	
	t_data *data;

	data = malloc(sizeof(t_data));
	if (!data)
	{
		return(NULL);
	}

	data->start_time = get_timestamp_in_ms();
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);

	if (argc == 6)
		data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		data->number_of_times_each_philosopher_must_eat = -1;
	
	pthread_mutex_init(&data->print, NULL);
	
	return (data);
}

t_philo *init_philos(t_data *data)
{
	t_philo *philos;
	int i;

	if (!data)
		return (NULL);

	philos = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (!philos)
	{
		return (NULL);
	}
	
	i = 0;
	while (i < data->number_of_philosophers)
	{
		philos[i].id = i + 1;
		pthread_mutex_init(&philos[i].right_fork_own, NULL);
		philos[i].data = data;
		i++;
	}
	
	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (i == data->number_of_philosophers - 1)
		{
			philos[i].left_fork_neighbor = &philos[0].right_fork_own;
		}
		else 
		{
			philos[i].left_fork_neighbor = &philos[i + 1].right_fork_own;
		}
		i++;
	}

	return (philos);
}

bool create_threads(t_data *data, t_philo *philos)
{
	int n; // TODO: replace w i
	
	n = 0;
	while (n < data->number_of_philosophers)
	{
		if (pthread_create(&philos[n].thread, NULL, &routine, &philos[n]) != 0)
			return (false);
		n++;
	}
	n = 0;
	while (n < data->number_of_philosophers)
	{
		if (pthread_join(philos[n].thread, NULL) != 0)
			return (false); 
		n++;
	}

	return (true);
}
