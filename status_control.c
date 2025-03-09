#include "philo.h"

static int	philos_eating_count(t_philo *philos)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < philos->n_philos)
	{
		if (pthread_mutex_lock(philos->lock_meal))
		{
			ft_putendl_fd("Error: Mutex Lock Failed!", 2);
			return (-1);
		}
		if (philos[i].meals_eaten >= philos->n_eat)
			count++;
		if (pthread_mutex_unlock(philos->lock_meal))
		{
			ft_putendl_fd("Error: Mutex Lock Failed!", 2);
			return (-1);
		}
		i++;
	}
	return (count);
}

int eating_endup_check(t_philo *philos)
{
    int count;

    count = 0;
    if (philos->n_eat == -1)
		return (0);
    count = philos_eating_count(philos);
    if (count == -1)
		return (1);
    if (count == philos->n_philos)
    {
        if (pthread_mutex_lock(philos->lock_dead))
			return (error_out("Error: Mutex Lock Failed!"));
        *(philos->dead) = 1;
        if (pthread_mutex_unlock(philos->lock_dead))
			return (error_out("Error: Mutex Unlock Failed!"));
        return (1);
    }
    return (0);
}

static int hunger_check(t_philo *philo)
{
    time_t time;

    if (pthread_mutex_lock(philo->lock_meal))
        return (error_out("Error: Mutex Lock Failed!"));
    time = current_time();
    if (time == -1)
    {
        pthread_mutex_unlock(philo->lock_meal);
        return (1);
    }
    if (time - philo->last_meal >= philo->t_die && philo->is_eating == 0) // if the time exceeded the amount time which indicated for starving the philo then ...
    {
        if (pthread_mutex_unlock(philo->lock_meal))
            return(error_out("Error: Mutex Unlock Failed!"));
        return (1);
    }
    if (pthread_mutex_unlock(philo->lock_meal))
        return (error_out("Error: Mutex Unlock Failed!"));
    return (0);
}

int dead_check(t_philo *philos)
{
    int i;

    i = 0;
    while (i < philos->n_philos)
    {
        if (hunger_check(&philos[i]))
        {
            if (log_printing(&philos[i], "died", 1)) // we should write it here!!
                return (1);
            if (pthread_mutex_lock(philos->lock_dead))
                return (error_out("Error: Mutex Lock Failed!"));
            *(philos->dead) = 1; // why ???????
            if (pthread_mutex_unlock(philos->lock_dead))
                return (error_out("Error: Mutex unlock failed"));
            return (1);
        }
        i++;
    }
    return (0);
}