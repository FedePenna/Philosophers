#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/types.h>
# include <time.h>
# include <unistd.h>

typedef struct s_table
{
	int				ph_num;
	long			time_to_eat;
	long			time_to_die;
	long			bedtime;
	int				max_eat;
	int				all_ate;
	int				dead;
	long			tstart;
	pthread_mutex_t	*forks;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	print;
	struct s_philo	*philos;
}					t_table;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	int				eaten_meals;
	long			last_meal;
	pthread_t		thread;
	t_table			*table;
}					t_philo;

int					ft_atoi(const char *str);
int					ft_isnumber(char *str);
int					check_arg(char **av);
int					main(int ac, char **av);
int					init_table(t_table *table, int ac, char **av);
long				get_time(void);
void				sim_start(t_table *table);
void    sort_fork(t_philo *philos, pthread_mutex_t **first,
    pthread_mutex_t **second);
void    print_action(t_philo *philo, const char *action);
void smart_sleep(long time_in_ms, t_table *table);
void    *monitoring(void *arg);
#endif
