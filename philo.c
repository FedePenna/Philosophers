#include "philo.h"

void    *phroutine(void *arg)
{
    t_philo         *philo;
    pthread_mutex_t *first;
    pthread_mutex_t *second;
    int             working;

    if (philo->id % 2 == 0)
        usleep(1000);
    while(1)
    {
        pthread_mutex_lock(&philo->table->dead_mutex);
        working = (!philo->table->dead && !philo->table->all_ate);
        pthread_mutex_unlock(&philo->table->dead_mutex);
        if (!working)
            break ;
        print_action(philo, "is thinking");
        sort_fork(philo, &first, &second);
        get_meal(philo, &first, &second);
        r_u_breathing(philo, first, second);
    }
}   

void    sim_start(t_table *table)
{
    int i;
    pthread_t monitor_thread;

    i = 0;
    while(i < table->ph_num)
    {
        table->philo[i].last_meal = get_time();
        if (pthread_create(&table->philo[i].thread), NULL, phroutine,
            &table->philo[i]) != 0
        {
            printf("Error: Thread Creation Failed");
            return ;
        }
        i++;
    }
    if (pthread_create(&monitor_thread, NULL, monitoring, table) != 0)
    {
        printf("Error: Monitor thread wasn't created");
        return ;
    }
    pthread_detach(monitor_thread);
    i = 0;
    while(i < table->ph_num)
    {
        pthread_join(table->philo[i].thread, NULL);
        i++;
    }
}
