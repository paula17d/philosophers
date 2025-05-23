/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:17:03 by pdrettas          #+#    #+#             */
/*   Updated: 2025/05/23 21:15:55 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

/*
destroys all mutexes and frees the data and philo struct.
note: left_fork_neighbor mutex does not need to be destroyed 
since it is only a pointer to the right_fork_own.
*/
void	free_all(t_data *data, t_philo *philos, char **argv)
{
	int	i;

	if (data != NULL)
	{
		pthread_mutex_destroy(&data->print);
		pthread_mutex_destroy(&data->time);
		free(data);
	}
	i = 0;
	if (philos != NULL)
	{
		while (i < ft_atoi(argv[1]))
		{
			pthread_mutex_destroy(&philos[i].right_fork_own);
			i++;
		}
		free(philos);
	}
}
