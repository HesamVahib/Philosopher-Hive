/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvahib <hvahib@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:16:16 by hvahib            #+#    #+#             */
/*   Updated: 2025/04/23 12:28:38 by hvahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	args_check(char **av)
{
	int	i;

	i = 1;
	if (ft_atoi(av[1]) > MAX_PHILO)
		return (error_out("Error: Select less Philosophers!"));
	while (av[i])
	{
		if ((!ft_isdigit(av[i])) || (ft_atoi(av[i]) <= 0))
			return (error_out("Error: Arguments should be positive numbers"));
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_manager		manager;
	t_philo			philos[MAX_PHILO];
	pthread_mutex_t	forks[MAX_PHILO];

	if (ac != 5 && ac != 6)
		return (error_out("Error: Invalid number of Arguments"));
	if (args_check(av))
		return (0);
	init_manager(&manager, philos);
	init_forks(&manager, forks, ft_atoi(av[1]));
	init_philos(&manager, philos, forks, av);
	lets_eat(&manager, forks);
	termination(NULL, &manager, forks);
	return (0);
}
