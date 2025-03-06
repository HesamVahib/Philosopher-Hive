#include "philo.h"

void    lets_eat(t_manager *manager, pthread_mutex_t *forks)
{
    int i;
    pthread_t   controller; // it is a number to enable the programmer to deal with threads

    i = 0;
    controller = create_thread(manager, forks); // having controller just to check if it is failed or not... we should have created it
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