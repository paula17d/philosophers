/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauladrettas <pauladrettas@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 21:12:06 by pauladretta       #+#    #+#             */
/*   Updated: 2025/05/13 01:11:35 by pauladretta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// calculates milliseconds since 1972
long	get_timestamp_in_ms(void) // TODO: adjust
{
	struct timeval	tv;
	long			time_in_ms;

	gettimeofday(&tv, NULL);
	time_in_ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time_in_ms);
}

// own calculated usleep to have no delay (in terminal output)
void ft_usleep(long millsec) // same input as usleep
{
	long time;

    // aktuelle zeit + zeit die geschlafen wird
	time = get_timestamp_in_ms() + millsec;
    // goes on as long as its not time where its supposed to stop from above
	// NOT !=, bc sometimes it can be one ms above and continues to grow
    // so its gotta be smaller
    while (get_timestamp_in_ms() < time) 
    {
        // to save resources so its not while all the time
		usleep(35); // ex. 500 too much delay (died)
    }
}
