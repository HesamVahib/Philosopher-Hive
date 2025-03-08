#include "philo.h"

static int is_single_philo(t_philo *philo)
{
    if (philo->n_philos == 1)
    {
        if (ft_usleep(philo->t_die))
            return (error_out("Error: uSleep Failed!"));
        if (pthread_mutex_unlock(philo->r_fork))
            return (error_out("Error: Mutex Unlock Failed!"));
    }
    return (0);
}

static int forks_handling(t_philo *philo, char c)
{
    if (c == 'L')
    {
        if (pthread_mutex_lock(philo->l_fork))
            return (error_out("Error: Mutex Lock Failed!"));
        if (log_printing(philo, "has picked a fork", 0))
            return (1);
    }
    else
    {
        if (pthread_mutex_lock(philo->r_fork))
            return (error_out("Error: Mutex Lock Failed!"));
        if (log_printing(philo, "has picked a fork", 0))
            return (1);
    }
    return (0);
}

int eating(t_philo *philo)
{
    if (forks_handling(philo, 'R'))
        return (1);
    if (is_single_philo(philo))
        return (1);
    if (forks_handling(philo, 'L'))
        return (1);
    philo->is_eating = 1;
    if (log_printing(philo, "is eating", 0))
        return (1);
    if (pthread_mutex_lock(philo->lock_meal))
        return (error_out("Error: Mutex Lock Failed!"));
    philo->last_meal = current_time();
    if (philo->last_meal == -1)
        return (1);
    philo->meals_eaten++;
    if (pthread_mutex_unlock(philo->lock_meal))
        return (error_out("Error: Mutex Unlock Failed!"));
    if (ft_usleep(philo->t_eat))
        return (error_out("Error: uSleep Failed!"));
    philo->is_eating = 0;
    if (pthread_mutex_unlock(philo->l_fork))
        return (error_out("Error: Mutex Unlock Failed!"));
    if (pthread_mutex_unlock(philo->r_fork))
        return (error_out("Error: Mutex Unlock Failed!"));
    return (0);
}

int sleeping(t_philo *philo)
{
    if (log_printing(philo, "is sleeping", 0))
        return (1);
    if (ft_usleep(philo->t_sleep))
    {
        ft_putendl_fd("Error: Usleep failed", 2);
		return (1);
    }
    return (0);
}

int thinking(t_philo *philo)
{
    if (log_printing(philo, "is thinking", 0))
        return (1);
    return (0);
}