#include "philo.h"

void    init_manager(t_manager *manager, t_philo *philos) // initialize the lock for resources
{
    manager->is_dead = 0;
    manager->philos = philos;
    
    if (pthread_mutex_init(&(manager->lock_write), NULL)
        || pthread_mutex_init(&(manager->lock_dead), NULL)
        || pthread_mutex_init(&(manager->lock_meal), NULL))
        return (termination("Error: Mutex Initialisation Failed", manager, NULL)) ; //  if init fail in one or more init mutex terminate all of them.
}

void    init_forks(t_manager *manager, pthread_mutex_t *forks, int  num_forks)
{
    int i;

    i = 0;
    while (i < num_forks)
    {
        if (pthread_mutex_init(&forks[i], NULL))
            return (termination("Error: Mutex init failed in fork_init", manager, forks)) ;
        i++;
    }
}

static  void ceremony_scenario(t_philo   *philo, char **av)
{
    philo->n_philos = ft_atoi(av[1]);
	philo->t_die = ft_atoi(av[2]);
	philo->t_eat = ft_atoi(av[3]);
	philo->t_sleep = ft_atoi(av[4]);
	if (av[5])
		philo->n_eat = ft_atoi(av[5]);
	else
		philo->n_eat = -1;
}

static void philo_init_character(t_manager *manager, t_philo   *philo, pthread_mutex_t *forks, int i, int   philo_num)
{
	philo->id = i+1;
	philo->is_eating = 0;
	philo->meals_eaten = 0;
	philo->dead = &(manager->is_dead);
	philo->r_fork = &forks[i];
    if (i == 0)
        philo->l_fork = &forks[philo_num - 1];
    else
        philo->l_fork = &forks[i - 1];
	philo->lock_write = &(manager->lock_write);
	philo->lock_dead = &(manager->lock_dead);
	philo->lock_meal = &(manager->lock_meal);
}

void    init_philos(t_manager   *manager, t_philo   *philos, pthread_mutex_t *forks, char **av)
{
    int i;
    int philo_num;

    i = 0;
    philo_num = ft_atoi(av[1]);
    while (i < philo_num)
    {
        philos[1].start_time = current_time();
        if (philos[1].start_time == -1)
            return (termination(NULL, manager, forks)) ;
        philos[i].last_meal = current_time();
        if (philos[i].last_meal == -1)
            return (termination(NULL, manager, forks)) ;
        ceremony_scenario(&philos[i], av);
        philo_init_character(manager, &philos[i], forks, i, philo_num);
        i++;
    }
}