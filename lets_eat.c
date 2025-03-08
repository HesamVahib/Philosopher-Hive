#include "philo.h"

static void *status_control(void *arg)
{
    t_philo *philos;

    philos = (t_philo *)arg; // ??? (we are casting the arg wwhich is casted from manager philos)
    while (1) // now we are going to check it constantly till one of condition is statisfied
    {
        if (dead_check(philos) || eating_endup_check(philos))
            break ;
    }
    return (arg);
}

static void *ceremony(void *arg)
{
    int result;
    t_philo *philo;

    result = 0;
    philo = (t_philo *)arg;
    if (philo->id % 2 == 0)
        result = ft_usleep(3000);
    else if (philo->id != 1 && philo->id == philo->n_philos && philo->id % 2 != 0)
        result = ft_usleep(6000);
    if (result == -1)
    {
        ft_putendl_fd("Error: Usleep Failed", 2);
        return (NULL);
    }
    while (!dead_lock_check(philo))
    {
		if (eating(philo) || sleeping(philo)
			|| thinking(philo))
			return (NULL);
	}
    return (arg);
}

static pthread_t    threads_creation(t_manager *manager, pthread_mutex_t *forks)
{
    int i;
    pthread_t   thread_num;

    if (pthread_create(&thread_num, NULL, &status_control, manager->philos))
        return (termination("Error: Creating thread failed", manager, forks), 0);
    i = 0;
    while (i < manager->philos->n_philos)
    {
        if (pthread_create(&(manager->philos[i].thread), NULL, &ceremony, &(manager->philos[i])))
        {
            termination("Error: Thread Creation Failed", manager, forks);
            break ;
        }
        i++;
    }
    return (thread_num);
}

void    lets_eat(t_manager *manager, pthread_mutex_t *forks)
{
    int i;
    pthread_t   controller; // it is a number to enable the programmer to deal with threads (simply it is a number of a thread)

    i = 0;
    controller = threads_creation(manager, forks); // having controller just to check if it is failed or not... we should have created it
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