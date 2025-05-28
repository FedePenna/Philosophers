#include "philo.h"

void    print_action(t_philo *philo, const char *action)
{
    long    time;

    pthread_mutex_lock(&philo->table->print);
    pthread_mutex_lock(&philo->table->dead);
    if (!philo->table->dead)
    {
        time = get_time() - philo->table->tstart;
        printf("%ld philo %d %s\n", time, philo->id, action);
    }
    pthread_mutex_unlock(&philo->table->print);
    pthread_mutex_unlock(&philo->table->dead);
}

void    sort_fork(t_philo philos, pthread_mutex_t **first, pthread_mutex_t **second)
{
    if (philo_id < (philo_id + 1) % philo->table->ph_num)
    {
        *first = philo->left_fork;
        *second = philo->fork_right;
    }
    else
    {
        *first = philo->fork_right;
        *second = philo->left_fork;
    }
}
