/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fepennar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:47:58 by fepennar          #+#    #+#             */
/*   Updated: 2025/06/09 18:47:59 by fepennar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	smart_sleep(long time_in_ms, t_table *table)
{
	long	start;

	start = get_time();
	while (get_time() - start < time_in_ms)
	{
		pthread_mutex_lock(&table->dead_mutex);
		if (table->dead)
		{
			pthread_mutex_unlock(&table->dead_mutex);
			break ;
		}
		pthread_mutex_unlock(&table->dead_mutex);
		usleep(100);
	}
}

void	print_action(t_philo *philo, const char *action)
{
	long	time_now;
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&table->dead_mutex);
	if (table->dead)
	{
		pthread_mutex_unlock(&table->dead_mutex);
		return ;
	}
	time_now = get_time() - table->tstart;
	pthread_mutex_unlock(&table->dead_mutex);
	pthread_mutex_lock(&table->print);
	printf("%ld philo %d %s\n", time_now, philo->id, action);
	pthread_mutex_unlock(&table->print);
}

void	sort_fork(t_philo *philo, pthread_mutex_t **first,
		pthread_mutex_t **second)
{
	if (philo->id % 2 == 0)
	{
		*first = philo->fork_right;
		*second = philo->fork_left;
	}
	else
	{
		*first = philo->fork_left;
		*second = philo->fork_right;
	}
}
