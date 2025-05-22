/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauladrettas <pauladrettas@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:17:00 by pdrettas          #+#    #+#             */
/*   Updated: 2025/05/22 20:28:47 by pauladretta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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
	ft_usleep(data->time_to_eat);
}

void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork_neighbor);
	pthread_mutex_unlock(&philo->right_fork_own);
}

void	get_sleep(t_philo *philo, t_data *data)
{
	print_message("is sleeping", philo, data);
	ft_usleep(data->time_to_sleep);
}

void	think(t_philo *philo, t_data *data)
{
	print_message("is thinking", philo, data);
}

