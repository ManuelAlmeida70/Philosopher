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

void wait_all_threads(t_table *table)
{
    while (get_bool(&table->table_mutex, &table->all_threads_ready))
        ;
}