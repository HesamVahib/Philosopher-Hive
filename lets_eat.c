/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lets_eat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvahib <hvahib@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:12:06 by hvahib            #+#    #+#             */
/*   Updated: 2025/04/23 12:28:45 by hvahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*status_control(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	while (1)
	{
		if (dead_check(philos) || eating_endup_check(philos))
			break ;
	}
	return (arg);
}

static void	*ceremony(void *arg)
{
	int		result;
	t_philo	*philo;

	result = 0;
	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		result = usleep(3000);
	else if (philo->id != 1 && philo->id == philo->n_philos
		&& philo->id % 2 != 0)
		result = usleep(1500);
	if (result == -1)
	{
		ft_putendl_fd("Error: uSleep Failed!", 2);
		return (NULL);
	}
	while (!dead_lock_check(philo))
	{
		if (eating(philo) || sleeping(philo) || thinking(philo))
			return (NULL);
	}
	return (arg);
}

static pthread_t	threads_creation(t_manager *manager, pthread_mutex_t *forks)
{
	int			i;
	pthread_t	thread_num;

	if (pthread_create(&thread_num, NULL, &status_control, manager->philos))
		return (termination("Error: Creating thread failed",
				manager, forks), 0);
	i = 0;
	while (i < manager->philos->n_philos)
	{
		if (pthread_create(&(manager->philos[i].thread),
				NULL, &ceremony, &(manager->philos[i])))
		{
			termination("Error: Thread Creation Failed", manager, forks);
			return (0);
		}
		i++;
	}
	return (thread_num);
}

void	lets_eat(t_manager *manager, pthread_mutex_t *forks)
{
	int			i;
	pthread_t	controller;

	i = 0;
	controller = threads_creation(manager, forks);
	if (!controller)
		return ;
	if (pthread_join(controller, NULL))
	{
		termination("Error: failed in joining thread", manager, forks);
		return ;
	}
	while (i < manager->philos->n_philos)
	{
		if (pthread_join(manager->philos[i].thread, NULL))
		{
			termination("Error: failed in joining thread", manager, forks);
			return ;
		}
		i++;
	}
}
