/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalmeid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:00:18 by maalmeid          #+#    #+#             */
/*   Updated: 2024/10/18 17:14:08 by maalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline bool	is_space(char ch)
{
	return ((ch >= 9 && ch <= 13) || ch == 32);
}

static inline bool	is_digit(char ch)
{
	return (ch >= '0' && ch <= '9');
}

static const char	*valid_input(const char *str)
{
	int			len;
	const char	*number;

	len = 0;
	while (is_space(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		error_exit("Feed me only positive values u suck");
	if (!is_digit(*str))
		error_exit("The input is not a correct digit");
	number = str;
	while (is_digit(*str++))
		len++;
	if (len > 10)
		error_exit("The value it too big, INT MAX is the limit");
	return (number);
}

static long	ft_atol(const char *str)
{
	long	num;

	num = 0;
	str = valid_input(str);
	while (is_digit(*str))
		num = (num * 10) + ((*str++) - 48);
	if (num > INT_MAX)
		error_exit("The value is too big, INT_MAX is thre limit");
	return (num);
}

void	parse_input(t_table *table, char **av)
{
	table->philo_nb = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * 1e3;
	table->time_to_eat = ft_atol(av[3]) * 1e3;
	table->time_to_sleep = ft_atol(av[4]) * 1e3;
	if (table->time_to_die < 6e4
		|| table->time_to_eat < 6e4
		|| table->time_to_sleep < 6e4)
		error_exit("Use timestamps major than 60ms");
	if (av[5])
		table->nbr_limit_meals = ft_atol(av[5]);
	else
		table->nbr_limit_meals = -1;
}