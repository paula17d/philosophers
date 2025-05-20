/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:17:00 by pdrettas          #+#    #+#             */
/*   Updated: 2025/05/20 18:19:06 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/*
When a philosopher has finished eating,
they put their forks back on the table
and start sleeping.
Once awake, they start thinking again.
The simulation stops when a philosopher dies of starvation.

If a philosopher waits too long to acquire forks because others are eating,
	they won’t get a chance to eat before dying.
they just wait for forks (dont sleep or think)
*/

// calculates time
void	print_message(char *msg, t_philo *philo, t_data *data)
{
	long	current_time;

	long current_time_lived_philo;
		// amount of time lived as of now since eating
	current_time = get_timestamp_in_ms() - data->start_time;
	current_time_lived_philo = get_timestamp_in_ms() - philo->time_since_eating;
	// if der letzte 8x+ gegessen hat
	// mutex so its not incremented or checked at same time
	// pthread_mutex_lock(&data->meals); // to prevent read & write data race
	// pthread_mutex_unlock(&data->meals);
	pthread_mutex_lock(&data->print);
	// added check for death (not needed) (death_monitor already takes care of it)
	// if (current_time_lived_philo > data->time_to_die && data->death_of_philo == false)
	// {
	// 	data->death_of_philo = true;
	// 	printf("%lu %d died\n", current_time, philo->id);
	// 	pthread_mutex_unlock(&data->print);
	// 	return ;
	// }
	if (ft_strcmp(msg, "is eating") == 0 && data->death_of_philo == false)
	{
		data->meals_completed++;
	}
	if (data->meals_completed > (data->number_of_times_each_philosopher_must_eat
			* data->number_of_philosophers))
	{
		data->death_of_philo = true;
		// also means simulation done basically
	}
	else if (data->death_of_philo == false)
	{
		printf("%lu %d %s\n", current_time, philo->id, msg);
	}
	pthread_mutex_unlock(&data->print);
}

void	take_forks(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&philo->right_fork_own);
	print_message("has taken a fork", philo, data);
	pthread_mutex_lock(philo->left_fork_neighbor);
	print_message("has taken a fork", philo, data);
}

void	eat(t_philo *philo, t_data *data)
{
	print_message("is eating", philo, data);
	ft_usleep(data->time_to_eat); // TODO: if lots of delay, code own usleep
	// pthread_mutex_lock(&data->print);
		// write data race: multiple threads could increment at the same time so its only increment one which is wrong (a=3 to a=4 w multiple)
	// data->meals_completed++;
	// pthread_mutex_unlock(&data->print);
	// printf("**meals completed = %d**\n", data->meals_completed);
}

void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork_neighbor);
	pthread_mutex_unlock(&philo->right_fork_own);
	// print_message("has put down a fork", philo, data);
		// TODO: delete (for testing)
	// print_message("has put down a fork", philo, data);
		// TODO: delete (for testing)
}

void	get_sleep(t_philo *philo, t_data *data)
{
	print_message("is sleeping", philo, data);
	ft_usleep(data->time_to_sleep); // multiply by 1000 to get ms
}

void	think(t_philo *philo, t_data *data)
{
	print_message("is thinking", philo, data);
}

bool	is_dead(t_data *data)
{
	pthread_mutex_lock(&data->print);
	if (data->death_of_philo == false)
	{
		pthread_mutex_unlock(&data->print);
		return (false);
	}
	else
	{
		pthread_mutex_unlock(&data->print);
		return (true);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	// only one philo bc only one philo is input in one thread creation
	philo = (t_philo *)arg;
	data = philo->data;
	// printf("id philo = %d\n", philo->id);
	if (philo->id % 2 == 0 || (philo->id == data->number_of_philosophers
			&& data->number_of_philosophers != 1))
	{
		think(philo, data);
		ft_usleep((data->time_to_eat) / 2); // so that even ones wait more (/2)
	}
	// time to die nach 30 seg
	while (is_dead(data) == false)
	{
		// ft_usleep(52);
		// 	if (data->meals_completed >= (data->number_of_times_each_philosopher_must_eat * data->number_of_philosophers))
		// {
		// 	data->death_of_philo = true; // also means simulation done basically
		// }
		// pthread_mutex_lock(&data->test);
		take_forks(philo, data);
		pthread_mutex_lock(&data->time);
		philo->time_since_eating = get_timestamp_in_ms(); // 20:00
			// time is updated to current time after each while iteration
		pthread_mutex_unlock(&data->time);
		eat(philo, data);      // 20:10 (DONE EATING)
			// check: if timetodie is smaller than one of the 4 actions, philo dies
		put_down_forks(philo); // 20:10
		// pthread_mutex_unlock(&data->test);
		get_sleep(philo, data); // 20:20
		think(philo, data);     // 20:40 zeitvergangen = 40 time to die = 30
	}
	// FT: taking forks
	// routine: even philos start w right fork. uneven w left fork (prevents deadlocks by avoiding circular waiting)
	// if (philo->ID % 2 == 0)
	// {
	// 	pthread_mutex_lock(&philo->data->forks[left_fork]);
			// TODO: all of this below needs fixing...
	// 	printf("has taken right fork\n");
	// 	pthread_mutex_lock(philo->left_fork);
	// 	printf("has taken left fork\n");
	// }
	// else
	// {
	// 	pthread_mutex_lock(philo->left_fork);
	// 	printf("has taken left fork\n");
	// 	pthread_mutex_lock(philo->right_fork);
	// 	printf("has taken right fork\n");
	// }
	return (NULL);
}

// MUTEX:
/*
- is meant to be shared btw threads
- needs to exist before threads start and persist while they run:
-- initialize mutex before creating threads
-- destroy it after all threads finish
*/

/*
When a philosopher has finished eating,
	they put their forks back on the table and
start sleeping. Once awake, they start thinking again. The simulation stops when
a philosopher dies of starvation.
*/

/*
PRINTING FORMAT (have timestamps in philo struct)
◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
*/
