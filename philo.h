#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

# define MAX_PHILO 400
# define ANSI_COLOR_RED "\001\x1b[31m\002"
# define ANSI_COLOR_RESET "\001\x1b[0m\002"

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
int	ft_isdigit(char *str);
void	termination(char *str, t_manager *manager, pthread_mutex_t *forks);
void	init_forks(t_manager *manager, pthread_mutex_t *forks, int  num_forks);
void	init_manager(t_manager *manager, t_philo *philos);
void	lets_eat(t_manager *manager, pthread_mutex_t *forks);
int	log_printing(t_philo *philo, char *str, int dead);
int	dead_lock_check(t_philo *philo);
int error_out(char *str);
int	ft_usleep(time_t ms);
time_t	current_time(void);

int eating(t_philo *philo);
int sleeping(t_philo *philo);
int thinking(t_philo *philo);

int dead_check(t_philo *philos);
int eating_endup_check(t_philo *philos);

void    init_philos(t_manager   *manager, t_philo   *philos, pthread_mutex_t *forks, char **av);


#endif