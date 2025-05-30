#include "philo.h"

void smart_sleep(long time_in_ms, t_table *table)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < time_in_ms)
	{
		pthread_mutex_lock(&table->dead_mutex);
		if (table->dead)
		{
			pthread_mutex_unlock(&table->dead_mutex);
			break;
		}
		pthread_mutex_unlock(&table->dead_mutex);
		usleep(100);
	}
}

void    print_action(t_philo *philo, const char *action)
{
    long    time;

    pthread_mutex_lock(&philo->table->print);
    pthread_mutex_lock(&philo->table->dead_mutex);
    if (!philo->table->dead)
    {
        time = get_time() - philo->table->tstart;
        printf("%ld philo %d %s\n", time, philo->id, action);
    }
    pthread_mutex_unlock(&philo->table->print);
    pthread_mutex_unlock(&philo->table->dead_mutex);
}

void    sort_fork(t_philo *philo, pthread_mutex_t **first,
    pthread_mutex_t **second)
{
    if (philo->id < (philo->id + 1) % philo->table->ph_num)
    {
        *first = philo->fork_left;
        *second = philo->fork_right;
    }
    else
    {
        *first = philo->fork_right;
        *second = philo->fork_left;
    }
}
