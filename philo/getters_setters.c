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

void set_bool(t_mtx *mutex, bool *dest, bool value)
{
    safe_mutex_handle(mutex, LOCK);
    *dest = value;
    safe_mutex_handle(mutex, UNLOCK);
}

bool get_bool(t_mtx *mutex, bool *value)
{
    bool re;

    safe_mutex_handle(mutex, LOCK);
    re = *value;
    safe_mutex_handle(mutex, UNLOCK);
    return (re);
}

void set_long(t_mtx *mutex, long *dest, long value)
{
    safe_mutex_handle(mutex, LOCK);
    *dest = value;
}

long get_long(t_mtx *mutex, long *value)
{
    long re;

    safe_mutex_handle(mutex, LOCK);
    re = *value;
    safe_mutex_handle(mutex, UNLOCK);
    return (re);
}

bool simulation_fineshed(t_table *table)
{
    return (get_bool(&table->table_mutex, &table->end_simulation));
}