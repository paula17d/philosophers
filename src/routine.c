/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:17:00 by pdrettas          #+#    #+#             */
/*   Updated: 2025/05/01 21:03:46 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// FT: think

// FT: take forks

// FT: eat

// FT: put down forks

// FT: sleep 


/*
When a philosopher has finished eating, 
they put their forks back on the table 
and start sleeping. 
Once awake, they start thinking again. 
The simulation stops when a philosopher dies of starvation.

If a philosopher waits too long to acquire forks because others are eating, they won’t get a chance to eat before dying.
they just wait for forks (dont sleep or think)


if a philo has both left & right fork (set equal to 1 (for condition statement in eat ft), THEN they can eat)
*/
void *routine(void *arg) // TODO: (ask t on how to have structs as input now)
{ 
	t_philo		*philo;
	t_data		*data;

	philo = (t_philo *)arg;
	data = philo->data;

	// TODO: number of forks is equal to number of philosophers. 
	
	// FT: taking forks
		// routine: even philos start w right fork. uneven w left fork (prevents deadlocks by avoiding circular waiting)
	if (philo->ID % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork); // TODO: all of this below needs fixing...
		printf("has taken right fork\n");
		pthread_mutex_lock(philo->left_fork);
		printf("has taken left fork\n");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		printf("has taken left fork\n");
		pthread_mutex_lock(philo->right_fork);
		printf("has taken right fork\n");
	}
	
	// FT: putting down forks
	// pthread_mutex_unlock(&data->mutex); // TODO: putting down forks

	// while (i < 10000000) //  TODO: change condition (this was jsut from testing)
	// {
	// 	pthread_mutex_lock(&data->mutex);
	// 	mails++; // increment number of mails // TODO: delete
	// 	printf("mails = %d\n", mails); // TODO: delete
	// 	pthread_mutex_unlock(&data->mutex); 
	// 	i++;
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
START W ONE PHILO FIRST
1. include print statements in each action function
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
