/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalmeid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:14:49 by maalmeid          #+#    #+#             */
/*   Updated: 2024/10/18 17:41:22 by maalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>

# define RST "\033[0m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;35m"
# define CYAN "\033[1;36m"
# define WHITE "\033[1;37m"

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH
}	t_opcode;

typedef struct s_fork
{
	int		fork_id;
	pthread_mutex_t		fork;
}	t_fork;

typedef struct s_philo
{
	int			id;
	long		meals_counter;
	bool		full;
	long		last_meal_time;
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	t_table		*table;
}	t_philo;

typedef struct s_table
{
	long		philo_nb;
	long		time_to_eat;
	long		time_to_die;
	long		time_to_sleep;
	long		nbr_limit_meals;
	long		start_simulation;
	long		end_simulation;
	t_fork		*forks;
	t_philo		*philos;
}	t_table;

//utils.c
void	error_exit(const char *error);

//parsing.c
void	parse_input(t_table *table, char **av);

//safe_function.c
void	*safe_malloc(size_t bytes);
void	safe_mutex_handle(pthread_mutex_t *mutex, t_opcode opcode);

#endif
