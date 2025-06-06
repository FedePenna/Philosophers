/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: federico-pennarola <federico-pennarola@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:18:55 by fepennar          #+#    #+#             */
/*   Updated: 2025/05/27 18:18:49 by federico-pe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(t_table *table)
{
	int	i;

	i = 0;
	if (table->forks)
	{
		while (i < table->ph_num)
		{
			pthread_mutex_destroy(&table->forks[i]);
			i++;
		}
		free(table->forks);
	}
	if (table->philos)
		free(table->philos);
	pthread_mutex_destroy(&table->print);
	pthread_mutex_destroy(&table->dead_mutex);
}

int	main(int ac, char **av)
{
	t_table	table;
//	int	n_philo;
	int	i;

	i = 1;
	if (ac != 5 && ac != 6)
		return (printf("ERROR: invalid arguments, dipshit\n"));
	while (i < ac)
	{
		if (!ft_isnumber(av[i]))
			return (0);
		i++;
	}
	if (init_table(&table, ac, av) == -1)
		return (0);
//	n_philo = ft_atoi(av[1]);
//	printf("%d\n", n_philo);
	if (table.ph_num == 1)
	{
		printf("0 1 has taken a fork\n");
		smart_sleep(table.time_to_die, &table);
		printf("%ld 1 died\n", table.time_to_die);
		cleanup(&table);
		return (0);
	}
	sim_start(&table);
	cleanup(&table);
	return (0);
}
