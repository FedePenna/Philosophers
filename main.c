/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fepennar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:18:55 by fepennar          #+#    #+#             */
/*   Updated: 2025/05/07 14:18:56 by fepennar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arg(char **av)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(av[i])
	{
		while (av[i][j])
		{
			if (ft_isnumber(av[i]) == 0)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac != 5 && ac != 6)
		return (printf("ERROR: invalid arguments, dipshit\n"));
	if (check_arg(av) == 0)
		return (0);
	if (init_data(&table, ac, av) == 0)
		return (0);
	if (ft_atoi(av[1]) == 1)
	{
		printf("0 1 has taken a fork\n");
		usleep(ft_atoi(av[2]));
		printf("%d 1 died\n", ft_atoi(av[2]));
		cleanup(&table);
		return (0);
	}
}
