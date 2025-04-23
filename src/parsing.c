/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 22:30:08 by pdrettas          #+#    #+#             */
/*   Updated: 2025/04/23 19:09:28 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	ft_atoi(const char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || \
	str[i] == '\r' || str[i] == '\f' || str[i] == '\v')
		i++;
	if (str[i] == '+')
	{
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

bool is_digit_string(char *str)
{
	int i;
	
	i = 0;
	while (str && str[i] != '\0')
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (false);
		i++;
	}
	return (true);
}

void input_example_message()
{
	printf("input example: [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [optional: number_of_times_each_philosopher_must_eat]\n");
}


// main for parsing.c
bool parse_input(int argc, char **argv)
{
	int i;
	// checks # of arguments
	if (argc < 5 || argc > 6)
	{
		printf("error: wrong number of arguments\n");
		input_example_message();
		return (false); // TODO: use exit or return
	}
	// checks # of philosophers
	if (ft_atoi(argv[1]) > 200)
	{
		printf("error: too many philosophers (> 200).\n");
		return (false);
	}
	// checks if all strings contain only digits & if so, don't exceed max of int
	i = 1;
	while (argv[i] != NULL)
	{
		if (is_digit_string(argv[i]) == 0)
		{
			printf("error: arguments must contain only numeric digits (0–9) and represent positive values.\n");
			input_example_message();
			return (false);
		}
		if (ft_atoi(argv[i]) > INT_MAX)
		{
			printf("error: argument too large. maximum allowed is 2,147,483,647.\n");
			return (false);
		}
		i++;
	}
	return (true);
}

/*
structure 
1. $check string if all digits (and if negative sign in beginning, return error. or do later after atoi)
2. $convert from string to integer
3. $check that no higher than INT_MAX
4. $check that no more than 200 philos
5. update struct values w those numbers (do in init.c)
*/

// new: bool -> is like an int but only return true (1) or false (0). makes code cleaner & readable
