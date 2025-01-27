

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>

# define STR_USAGE "\033[36mUsage: ./philo [num_philosophers] [time_to_die] \
[time_to_eat] [time_to_sleep] [num_meals]\n\033[0m"

# define STR_FORK "\033[32m has taken a fork\033[0m"
# define STR_SLEEP "\033[36m is sleeping\033[0m"
# define STR_EAT "\033[35m is eating\033[0m"
# define STR_THINK "\033[1;37m is thinking\033[0m"

typedef struct s_data	t_data;

typedef struct s_philosopher
{
	int			id;
	int			meals_eaten;
	int			left_fork;
	int			right_fork;
	long long	last_meal_time;
	pthread_t	thread;
	t_data		*data;
}	t_philosopher;

typedef struct s_data
{
	int					num_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat_count;
	int					someone_died;
	long long			start_time;
	pthread_mutex_t		*forks;
	pthread_mutex_t		meal_mutex;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		death_mutex;
	t_philosopher		*philosophers;
}	t_data;

// Thread_simulation functions
int			check_if_simulation_finished(t_data *data);
void		set_simulation_stopped(t_data *data);
int			lock_forks_left_first(t_philosopher *philo);
int			lock_forks_right_first(t_philosopher *philo);

// init.c
int			init_data(t_data *data, int argc, char **argv);
int			init_philosophers(t_data *data);
int			init_mutexes(t_data *data);

// utils.c
int			ft_atoi(const char *str);
int			validate_input(int argc, char **argv);
int			validate_number(const char *str);
void		print_status(t_data *data, int id, char *status);
void		clean_exit(t_data *data);

// Time functions
long long	get_time(void);
void		smart_sleep(long long time);

// monitoring.c
void		*monitor_philosophers(void *arg);

// actions.c
void		*philosopher_routine(void *arg);
void		release_forks(t_philosopher *philo);
int			take_forks(t_philosopher *philo);

#endif
