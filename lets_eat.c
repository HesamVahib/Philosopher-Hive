#include "philo.h"

void    lets_eat(t_manager *manager, pthread_mutex_t *forks)
{
    int i;
    pthread_t   control;

    control = create_thread(manager, forks);
    ///
}