#include "philo.h"

int check_all_ate(t_table *table)
{
    int i;

    i = 0;
    while (i < table->ph_num)
    {
        if (table->philos[i].eaten_meals < table->max_eat)
            return (0);
        i++;
    }
    return (1);
}

static int check_meals(t_table *table)
{
    pthread_mutex_lock(&table->dead_mutex);
    if (table->max_eat > 0 && check_all_ate(table))
    {
        table->all_ate = 1;
        pthread_mutex_unlock(&table->dead_mutex);
        return (1);
    }
    pthread_mutex_unlock(&table->dead_mutex);
    return (0);
}

static int check_death(t_table *table, int i, long now)
{
    long    last_meal;

    pthread_mutex_lock(&table->dead_mutex);
    last_meal = table->philos[i].last_meal;
    if ((now - last_meal) > table->time_to_die)
    {
        table->dead = 1;
        pthread_mutex_unlock(&table->dead_mutex);
        pthread_mutex_lock(&table->print);
        printf("%ld philo %d died\n", now - table->tstart,
            table->philos[i].id);
        pthread_mutex_unlock(&table->print);
        return (1); 
    }
    pthread_mutex_unlock(&table->dead_mutex);
    return (0);
}

void    *monitoring(void *arg)
{
    t_table *table;
    int     i;
    long    now;

    table = (t_table *)arg;
    while(1)
    {
        now = get_time();
        i = 0;
        while (i < table->ph_num)
        {
            if (check_death(table, i, now) || check_meals(table))
                return (NULL);
            i++;
        }
        usleep(1000);
    }
}
