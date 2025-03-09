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
		// if (&(manager->lock_write)) // might have a problem because it is always there the address and it is said that destroying on uninitialized value might cause core dump!
		// 	if (pthread_mutex_destroy(&(manager->lock_write)))
		// 		ft_putendl_fd("Error: Mutex in lock_write destroy failed", 2);
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

int dead_lock_check(t_philo *philo)
{
    int is_dead;

    if (pthread_mutex_lock(philo->lock_dead))
        return (error_out("Error: Mutex lock failed"));
    is_dead = *(philo->dead);
    if (pthread_mutex_unlock(philo->lock_dead))
        return (error_out("Error: Mutex unlock failed"));
    return (is_dead);
}

int log_printing(t_philo *philo, char *str, int dead)
{
	time_t time;

	if (pthread_mutex_lock(philo->lock_write))
		return	(error_out("Error: Mutex Lock Failed!"));
	time = current_time();
	if (time < 0)
		return (1);
	time = time - philo->start_time;
	if (!dead_lock_check(philo))
	{
		if (dead == 0)
			printf("%ld\t%d\t%s\n", time, philo->id, str);
		else
		printf(ANSI_COLOR_RED"%ld\t%d\t%s\n"ANSI_COLOR_RESET,
				time, philo->id, str);
	}
	if (pthread_mutex_unlock(philo->lock_write))
		return (error_out("Error: Mutex unlock failed"));
	return (0);
}