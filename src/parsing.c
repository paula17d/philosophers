/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauladrettas <pauladrettas@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 22:30:08 by pdrettas          #+#    #+#             */
/*   Updated: 2025/05/20 20:54:53 by pauladretta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_messages(char *msg1, char *msg2);
long	ft_atoi(const char *str);
bool	is_digit_string(char *str);

/*
parse input by checking # of arguments, 
and making sure input consists of digits only, 
as well as not exceeding max of an int.
-> prints output message (error + input example) in case of error.
*/
bool	parse_input(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		print_messages(ERR_ARGS, MSG_INPUT);
		return (false);
	}

	i = 1;
	while (argv != NULL && argv[i] != NULL)
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

void	print_messages(char *msg1, char *msg2)
{
	if (msg1)
		printf("%s", msg1);
	if (msg2)
		printf("%s", msg2);
}

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

/*
check if string is empty, or consists of digits only.
*/
bool	is_digit_string(char *str)
{
	int	i;

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
