#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <sys/types.h>
# include <fcntl.h>
# include <time.h>
# include <errno.h>
# include <stdint.h>
# include <limits.h>

typedef struct s_philo
{
	int				philo_id;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	int				eaten_meals;
	long			last_meal;
	pthread_t		thread;
	struct s_table	*data;
}	t_philo;

typedef struct s_data
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
}	t_table;

typedef enum e_status
{
	DIED = 0,
	EATING = 1,
	SLEEPING = 2,
	THINKING = 3,
	GOT_FORK_1 = 4,
	GOT_FORK_2 = 5
}	t_status;

int	init_data(t_table *table, int ac, char **av);
int	ft_atoi(const char *str);
int	ft_isnumber(char c);
int	check_arg(char **av);
int	main(int ac, char **av);
long	get_time(void);

#endif
