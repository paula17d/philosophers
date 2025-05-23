/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 21:12:06 by pauladretta       #+#    #+#             */
/*   Updated: 2025/05/23 21:37:09 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// calculates milliseconds passed since 1972
long	get_timestamp_in_ms(void)
{
	struct timeval	current_time;
	long			time_in_ms;

	gettimeofday(&current_time, NULL);
	time_in_ms = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time_in_ms);
}

/*
custom sleep function that pauses execution for the given number of milliseconds
to avoid delay from the original usleep.
- calculates a target timestamp by adding the sleep duration to the current time.
- continuously checks the current time until the target is reached.
--> every 35ms if the full ex. 200ms has passed — more accurate.
--> ensures that sleep duration is as close as possible to the requested value.
- ensures more accurate timing than using `usleep(millsec * 1000)` directly,
   which can be too imprecise.
*/
void	ft_usleep(long millsec)
{
	long	time;

	time = get_timestamp_in_ms() + millsec;
	while (get_timestamp_in_ms() < time)
	{
		usleep(35);
	}
}
