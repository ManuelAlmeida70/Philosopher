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
# define DEBUG_MODE 1

typedef pthread_mutex_t t_mtx;
typedef struct s_philo t_philo;

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

typedef enum timecode
{
	SECOND,
	MILLISECOND,
	MICROSECOND
} t_timecode;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED
} t_philo_status;

typedef struct s_fork
{
	int		fork_id;
	t_mtx		fork;
}	t_fork;

typedef struct s_table
{
	long		philo_nb;
	long		time_to_eat;
	long		time_to_die;
	long		time_to_sleep;
	long		nbr_limit_meals;
	bool		start_simulation;
	bool		end_simulation;
	bool		all_threads_ready;
	pthread_t	monitor;
	t_mtx		table_mutex;
	t_mtx 		write_mutex;
	t_fork		*forks;
	t_philo		*philos;
}	t_table;

typedef struct s_philo
{
	int			id;
	long		meals_counter;
	bool		full;
	long		last_meal_time;
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	t_mtx		philo_mutex;
	t_table		*table;
}	t_philo;

//utils.c
void	error_exit(const char *error);
long get_time(t_timecode timecode);
void precise_usleep(long usec, t_table *table);

//parsing.c
void	parse_input(t_table *table, char **av);

//safe_function.c
void	*safe_malloc(size_t bytes);
void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
void safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, t_opcode opcode);

//dinner.c
void dinner_start(t_table *table);

//getters_setters.c
void set_bool(t_mtx *mutex, bool *dest, bool value);
bool get_bool(t_mtx *mutex, bool *value);
void set_long(t_mtx *mutex, long *dest, long value);
long get_long(t_mtx *mutex, long *value);
bool simulation_finished(t_table *table);

//synchro_utils.c
void wait_all_threads(t_table *table);

//init.c
void	data_init(t_table *table);
void clean(t_table *table);

//write.c
void write_status(t_philo_status status, t_philo *philo, bool debug);

#endif