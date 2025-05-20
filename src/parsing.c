/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrettas <pdrettas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 22:30:08 by pdrettas          #+#    #+#             */
/*   Updated: 2025/05/20 18:18:10 by pdrettas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	ft_atoi(const char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\f' || str[i] == '\v')
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

bool	is_digit_string(char *str)
{
	int	i;

	// if str is empty \0
	if (str[0] == '\0')
		return (false);
	i = 0;
	while (str && str[i] != '\0')
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (false);
		i++;
	}
	return (true);
}

// for cub3d [for adding, not printing]
// void	print_messages(const char *msg, ...)
// {
// 	va_list	args;
// 	const char *current;

// 	va_start(args, msg);
// 	current = msg;
// 	while (current)
// 	{
// 		printf("%s", current);
// 		current = va_arg(args, const char *);
// 	}
// 	va_end(args);
// }

void	print_messages(char *msg1, char *msg2)
{
	if (msg1)
		printf("%s", msg1);
	if (msg2)
		printf("%s", msg2);
}

// main for parsing.c
bool	parse_input(int argc, char **argv)
{
	int	i;

	// checks # of arguments
	if (argc < 5 || argc > 6)
	{
		print_messages(ERR_ARGS, MSG_INPUT);
		return (false); // TODO: use exit or return
	}
	// checks # of philosophers
	if (ft_atoi(argv[1]) > 200) // TODO: remove
	{
		print_messages(ERR_PHILOS, NULL);
		return (false);
	}
	// checks if all strings contain only digits & if so, don't exceed max of int
	i = 1;
	while (argv[i] != NULL)
	{
		if (is_digit_string(argv[i]) == 0)
		{
			print_messages(ERR_NUM, MSG_INPUT);
			return (false);
		}
		if (ft_atoi(argv[i]) > INT_MAX)
		{
			print_messages(ERR_NUM_MAX, MSG_INPUT);
			return (false);
		}
		i++;
	}
	return (true);
}
