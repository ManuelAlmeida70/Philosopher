/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalmeid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:58:01 by maalmeid          #+#    #+#             */
/*   Updated: 2025/02/05 15:58:10 by maalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	execute_philosopher_cycle(t_philosopher *philo)
{
	if (take_forks(philo) != 0)
		return (1);
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	print_status(philo->data, philo->id, STR_EAT);
	smart_sleep(philo->data->time_to_eat);
	release_forks(philo);
	if (check_if_simulation_finished(philo->data))
		return (1);
	if (philo->data->must_eat_count != -1
		&& philo->meals_eaten >= philo->data->must_eat_count)
		return (1);
	print_status(philo->data, philo->id, STR_SLEEP);
	smart_sleep(philo->data->time_to_sleep);
	if (check_if_simulation_finished(philo->data))
		return (1);
	print_status(philo->data, philo->id, STR_THINK);
	if (philo->data->num_philosophers > 2)
		usleep(500);
	return (0);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->data->num_philosophers == 1)
	{
		print_status(philo->data, philo->id, STR_FORK);
		smart_sleep(philo->data->time_to_die);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!check_if_simulation_finished(philo->data))
	{
		if (execute_philosopher_cycle(philo) != 0)
			break ;
	}
	return (NULL);
}

int	take_forks(t_philosopher *philo)
{
	int	error;

	if (check_if_simulation_finished(philo->data))
		return (1);
	if (philo->left_fork < philo->right_fork)
		error = lock_forks_left_first(philo);
	else
		error = lock_forks_right_first(philo);
	if (error)
		return (1);
	if (check_if_simulation_finished(philo->data))
	{
		release_forks(philo);
		return (1);
	}
	print_status(philo->data, philo->id, STR_FORK);
	print_status(philo->data, philo->id, STR_FORK);
	return (0);
}

void	release_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
}
