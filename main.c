/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvahib <hvahib@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:16:16 by hvahib            #+#    #+#             */
/*   Updated: 2025/04/24 10:48:59 by hvahib           ###   ########.fr       */
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

void	last_gathering(t_manager *manager)
{
	int	i;

	if (!manager || !manager->philos)
		return ;
	manager->philos = ft_calloc(manager->philos->n_philos, sizeof(t_philo));
	i = 0;
	while (i < manager->philos->n_philos)
	{
		if (pthread_join(manager->philos[i].thread, NULL) != 0)
			ft_putendl_fd("Error: pthread_join failed", 2);
		i++;
	}
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
	last_gathering(&manager);
	termination(NULL, &manager, forks);
	return (0);
}
