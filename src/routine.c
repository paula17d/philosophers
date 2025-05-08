/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:17:00 by pdrettas          #+#    #+#             */
/*   Updated: 2025/05/08 22:53:32 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/*
When a philosopher has finished eating, 
they put their forks back on the table 
and start sleeping. 
Once awake, they start thinking again. 
The simulation stops when a philosopher dies of starvation.

If a philosopher waits too long to acquire forks because others are eating, they won’t get a chance to eat before dying.
they just wait for forks (dont sleep or think)
*/

// calculates time
void print_message(char *msg, t_philo *philo, t_data *data)
{
	long current_time; 
	long current_time_lived_philo; // amount of time lived as of now since eating
	
	current_time = get_timestamp_in_ms() - data->start_time;
	current_time_lived_philo = get_timestamp_in_ms() - philo->time_since_eating;

	pthread_mutex_lock(&data->print);
	if (current_time_lived_philo > data->time_to_die)
	{
		data->death_of_philo = true;
		printf("%lu %d is dead\n", current_time, philo->id);
		return;
	}
	if (data->death_of_philo == false) 
	{
		printf("%lu %d %s\n", current_time, philo->id, msg);
	}
	pthread_mutex_unlock(&data->print);
}

void take_forks(t_philo	*philo, t_data *data)
{
	pthread_mutex_lock(&philo->right_fork_own);
	print_message("has taken a fork", philo, data);
	pthread_mutex_lock(philo->left_fork_neighbor);
	print_message("has taken a fork", philo, data);	
}

void eat(t_philo *philo, t_data *data)
{
	print_message("is eating", philo, data);
	usleep(data->time_to_eat * 1000); // TODO: if lots of delay, code own usleep
}

void put_down_forks(t_philo	*philo, t_data *data)
{
	pthread_mutex_unlock(&philo->right_fork_own); 
	print_message("has put down a fork", philo, data); // TODO: delete (for testing)
	pthread_mutex_unlock(philo->left_fork_neighbor);
	print_message("has put down a fork", philo, data); // TODO: delete (for testing)
}

void get_sleep(t_philo *philo, t_data *data)
{
	print_message("is sleeping", philo, data);
	usleep(data->time_to_sleep * 1000); // multiply by 1000 to get ms
}

void think(t_philo *philo, t_data *data)
{
	print_message("is thinking", philo, data);
}

bool is_dead(t_data *data)
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

void *routine(void *arg)
{ 
	// only one philo bc only one philo is input in one thread creation
	t_philo		*philo;
	t_data		*data;

	philo = (t_philo *)arg;
	data = philo->data;
	
	// printf("id philo = %d\n", philo->id);
	if (philo->id % 2 == 0)
	{
		usleep((data->time_to_eat * 1000) / 2); // so that even ones wait more (/2)
	}
	
	//time to die nach 30 seg
	while (is_dead(data) == false)
	{
		take_forks(philo, data);	
		philo->time_since_eating = get_timestamp_in_ms();//20:00 // time is updated to current time after each while iteration
		eat(philo, data);//20:10 (DONE EATING) // check: if timetodie is smaller than one of the 4 actions, philo dies
		put_down_forks(philo, data);//20:10
		get_sleep(philo, data);//20:20
		exit(0);
		think(philo, data);//20:40 zeitvergangen = 40 time to die = 30
	}
	
	

		

	
	// FT: taking forks
		// routine: even philos start w right fork. uneven w left fork (prevents deadlocks by avoiding circular waiting)
	// if (philo->ID % 2 == 0)
	// {
	// 	pthread_mutex_lock(&philo->data->forks[left_fork]); // TODO: all of this below needs fixing...
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
When a philosopher has finished eating, they put their forks back on the table and
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
