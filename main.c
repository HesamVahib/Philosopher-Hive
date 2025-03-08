#include "philo.h"

static int args_check(char **av)
{
    int i;

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

int main(int ac, char **av)
{
    t_manager       manager;
    t_philo       philos[MAX_PHILO];
    pthread_mutex_t forks[MAX_PHILO]; // having a lock for the resources (here is forks) to be used in order

    if (ac != 5 && ac != 6)
        return (error_out("Error: Invalid number of Arguements"));
    if (args_check(av))
        return (0);
    init_manager(&manager, philos); // i can just grab return and error out all in once
    init_forks(&manager, forks, ft_atoi(av[1]));
    lets_eat(&manager, forks);
    printf("rea ched here\n");
}