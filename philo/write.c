/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalmeid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:45:42 by maalmeid          #+#    #+#             */
/*   Updated: 2024/10/18 16:59:39 by maalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void write_status_debug(t_philo_status status, t_philo *philo, long elapsed)
{
    if (TAKE_FIRST_FORK == status && !simulation_finished(philo->table))
        printf(WHITE"%6ld"RST" %d has taken the 1st fork %d\n", elapsed, philo->first_fork->fork_id, philo->second_fork->fork_id);
    else if (TAKE_SECOND_FORK == status && !simulation_finished(philo->table))
        printf(WHITE"%6ld"RST" %d has taken the 2nd fork %d\n", elapsed, philo->id, philo->second_fork->fork_id);
    else if (EATING == status && !simulation_finished(philo->table))
        printf(WHITE"%6ld"CYAN" %d is eating %ld\n"RST, elapsed, philo->id, philo->meals_counter);
    else if (SLEEPING == status && !simulation_finished(philo->table))
        printf(WHITE"%ld"CYAN" %d is sleepin\n", elapsed, philo->id);
    else if (THINKING == status && !simulation_finished(philo->table))
        printf(WHITE"%6ld"RST" %d is thinking \n", elapsed, philo->id);
    else if (DIED == status)
        printf(RED"%6ld %d died\n"RST, elapsed, philo->id);
}

void write_status(t_philo_status status, t_philo *philo, bool debug)
{
    long elapsed;

    elapsed = get_time(MILLISECOND) - philo->table->start_time;
    if (philo->full)
        return ;
    safe_mutex_handle(&philo->table->write_mutex, LOCK);
    if (debug)
        write_status_debug(status, philo, elapsed);
    else
    {
        if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status) && !simulation_finished(philo->table))
            printf(WHITE"%-6ld"RST" %d has taken a fork\n", elapsed, philo->id);
        else if (EATING == status && !simulation_finished(philo->table))
            printf(WHITE"%-6ld"CYAN" %d is eating\n"RST, elapsed, philo->id);
        else if (SLEEPING == status && !simulation_finished(philo->table))
            printf(WHITE"%-6ld"RST" %d is sleeping\n", elapsed, philo->id);
        else if (THINKING == status && !simulation_finished(philo->table))
            printf(WHITE"%-6ld"RST" %d is thinking\n", elapsed, philo->id);
        else if (DIED == status)
            printf(RED"%-ld %d\n", elapsed, philo->id);
    }
    safe_mutex_handle(&philo->table->write_mutex, UNLOCK);
}