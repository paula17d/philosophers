/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:16:41 by pdrettas          #+#    #+#             */
/*   Updated: 2025/05/23 21:14:07 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	assign_forks(t_philo	*philos, t_data *data, int i);

t_data	*init_data(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
	{
		return (NULL);
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
	pthread_mutex_init(&data->time, NULL);
	data->stop_simulation = false;
	data->meals_completed = 0;
	return (data);
}

/*
initializes an array of philosopher structs.
- allocates memory for each philosopher.
- sets their ID, initial eating time, and a pointer to shared data.
- initializes a mutex for each philosopher's own right fork.
- assigns each philosopher a pointer to their neighbor's left fork
(i.e., the right fork of the next philosopher, circularly).
returns a pointer to the initialized array of philosophers.
*/
t_philo	*init_philos(t_data *data)
{
	t_philo	*philos;
	int		i;

	if (!data)
		return (NULL);
	philos = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		philos[i].time_of_eating = get_timestamp_in_ms();
		philos[i].id = i + 1;
		pthread_mutex_init(&philos[i].right_fork_own, NULL);
		philos[i].data = data;
		i++;
	}
	i = 0;
	while (i < data->number_of_philosophers)
	{
		assign_forks(philos, data, i);
		i++;
	}
	return (philos);
}

void	assign_forks(t_philo	*philos, t_data *data, int i)
{
	if (i == data->number_of_philosophers - 1)
	{
		philos[i].left_fork_neighbor = &philos[0].right_fork_own;
	}
	else
	{
		philos[i].left_fork_neighbor = &philos[i + 1].right_fork_own;
	}
}
