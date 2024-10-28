/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalmeid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:42:54 by maalmeid          #+#    #+#             */
/*   Updated: 2024/10/18 17:43:17 by maalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long get_time(t_timecode timecode)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL))
		error_exit("Get time of day failed");
	if (SECOND == timecode)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (MILLISECOND == timecode)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (MICROSECOND == timecode)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		error_exit("Wrong input to time");
	return (1337);
}

void precise_usleep(long usec, t_table *table)
{
	long start;
	long elapsed;
	long rem;

	start = get_time(MICROSECOND);
	while (get_time(MICROSECOND) - start < usec)
	{
		if (simulation_finished(table))
			break ;
		elapsed = get_time(MICROSECOND) - start;
		rem = usec - elapsed;
		if (rem > 1e3)
			usleep(rem / 2);// or usec / 2
		else
		{
			while (get_time(MICROSECOND) - start < usec)
				;
		}
	}
}

void	error_exit(const char *error)
{
	printf(RED"%s\n"RST, error);
	exit(EXIT_FAILURE);
}
