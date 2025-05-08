/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 21:12:06 by pauladretta       #+#    #+#             */
/*   Updated: 2025/05/08 19:08:43 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// 1972
long	get_timestamp_in_ms(void) // TODO: adjust
{
	struct timeval	tv;
	long			time_in_ms;

	gettimeofday(&tv, NULL);
	time_in_ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time_in_ms);
}
