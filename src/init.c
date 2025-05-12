/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauladrettas <pauladrettas@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:16:41 by pdrettas          #+#    #+#             */
/*   Updated: 2025/05/13 01:04:20 by pauladretta      ###   ########.fr       */
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
	pthread_mutex_init(&data->time, NULL);
	data->death_of_philo = false;
	
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
		philos[i].time_since_eating = get_timestamp_in_ms(); // compile time of progam
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

// checks if a philo has exceeded timetodie and sets death to true
bool death_monitor(t_philo *philo, t_data *data)
{
	long current_time; 
	long current_time_lived_philo;
	
	current_time = get_timestamp_in_ms() - data->start_time;
	pthread_mutex_lock(&data->time);
	current_time_lived_philo = get_timestamp_in_ms() - philo->time_since_eating;
	pthread_mutex_unlock(&data->time);

	pthread_mutex_lock(&data->print);
	if (data->death_of_philo == true)
	{
		pthread_mutex_unlock(&data->print);
		return (true);
	}
	if (current_time_lived_philo > data->time_to_die)
	{
		data->death_of_philo = true;
		printf("%lu %d died\n", current_time, philo->id);
		pthread_mutex_unlock(&data->print);
		return (true);
	}
	pthread_mutex_unlock(&data->print);
	return (false);
}

// checks if death of a philo has occured
bool monitor_all_philos(t_philo *philos, t_data *data)
{
	int i;

	i = 0;
	while (1)
	{
		if (death_monitor(&philos[i], data) == true)
		{
			return (true);
		}
		i++;
		if(i ==  data->number_of_philosophers)
			i=0;
	}
}

bool create_threads(t_data *data, t_philo *philos)
{
	int i;
	
	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_create(&philos[i].thread, NULL, &routine, &philos[i]) != 0) // create a thread (first variable) for each philo in the array (last variable)
			return (false);
		i++;
	}
	monitor_all_philos(philos, data);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
			return (false); 
		i++;
	}

	return (true);
}
