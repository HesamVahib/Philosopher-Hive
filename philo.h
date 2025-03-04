#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>

# define MAX_PHILO 400

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				is_eating;
	int				meals_eaten;
	int				n_philos;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
	int				*dead;
	time_t			start_time;
	time_t			last_meal;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*lock_write;
	pthread_mutex_t	*lock_dead;
	pthread_mutex_t	*lock_meal;
}					t_philo;

typedef struct s_manager
{
	int				is_dead;
	t_philo			*philos;
	pthread_mutex_t	lock_write;
	pthread_mutex_t	lock_dead;
	pthread_mutex_t	lock_meal;
}					t_manager;

void	ft_putendl_fd(char *s, int fd);
int	ft_atoi(const char *str);
int	ft_isdigit(int c);
void	termination(char *str, t_manager *manager, pthread_mutex_t *forks);
void    init_forks(t_manager *manager, pthread_mutex_t *forks, int  num_forks);
void    init_manager(t_manager *manager, t_philo *philos);

#endif