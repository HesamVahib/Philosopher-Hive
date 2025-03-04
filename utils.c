#include "philo.h"

int error_out(char *str)
{
    ft_putendl_fd(str, 2);
    return (1);
}

void	termination(char *str, t_manager *manager, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (str)
		ft_putendl_fd(str, 2);
	if (manager)
	{
		if (&(manager->lock_write))
			if (pthread_mutex_destroy(&(manager->lock_write)))
				ft_putendl_fd("Error: Mutex in lock_write destroy failed", 2);
		if (&(manager->lock_dead))
			if (pthread_mutex_destroy(&(manager->lock_dead)))
				ft_putendl_fd("Error: Mutex in lock_dead destroy failed", 2);
		if (&(manager->lock_meal))
			if (pthread_mutex_destroy(&(manager->lock_meal)))
				ft_putendl_fd("Error: Mutex in lock_meal destroy failed", 2);
		while (manager->philos->n_philos != 1 && i < manager->philos->n_philos
			&& &(forks[i]))
		{
			if (pthread_mutex_destroy(&forks[i]))
				ft_putendl_fd("Error: Mutex destroy failed", 2);
			i++;
		}
	}
}