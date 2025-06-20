/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fepennar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:44:58 by fepennar          #+#    #+#             */
/*   Updated: 2025/06/09 18:44:59 by fepennar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;
	long			time_in_ms;

	gettimeofday(&tv, NULL);
	time_in_ms = (tv.tv_sec * 1000);
	time_in_ms += (tv.tv_usec / 1000);
	return (time_in_ms);
}

static int	init_philos(t_table *table)
{
	int	i;

	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->ph_num);
	if (!table->philos)
		return (1);
	i = 0;
	while (i < table->ph_num)
	{
		table->philos[i].id = i + 1;
		table->philos[i].eaten_meals = 0;
		table->philos[i].last_meal = 0;
		table->philos[i].table = table;
		table->philos[i].fork_left = &table->forks[i];
		table->philos[i].fork_right = &table->forks[(i + 1) % table->ph_num];
		i++;
	}
	return (0);
}

static int	init_mutexes(t_table *table)
{
	int	i;

	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* table->ph_num);
	if (!table->forks)
		return (1);
	i = 0;
	while (i < table->ph_num)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&table->print, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&table->dead_mutex, NULL) != 0)
		return (1);
	return (0);
}

int	init_table(t_table *table, int ac, char **av)
{
	int	i;

	table->ph_num = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->bedtime = ft_atoi(av[4]);
	if (ac == 6)
		table->max_eat = ft_atoi(av[5]);
	else
		table->max_eat = -1;
	table->all_ate = 0;
	table->dead = 0;
	if (table->ph_num <= 0 || table->time_to_die <= 0 || table->time_to_eat <= 0
		|| table->bedtime <= 0 || (ac == 6 && table->max_eat <= 0))
		return (-1);
	if (init_mutexes(table) == 1)
		return (-1);
	if (init_philos(table) == 1)
		return (-1);
	table->tstart = get_time();
	i = -1;
	while (++i < table->ph_num)
		table->philos[i].last_meal = table->tstart;
	return (0);
}
