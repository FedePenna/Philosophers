#include "philo.h"

static int	philo_eat(t_philo *philo, pthread_mutex_t *first,
		pthread_mutex_t *second)
{
    t_table	*table;
	
	table = philo->table;
	pthread_mutex_lock(&table->dead_mutex);
    if (table->dead || table->all_ate)
    {
        pthread_mutex_unlock(second);
        pthread_mutex_unlock(first);
        pthread_mutex_unlock(&table->dead_mutex);
        return (0);
    }
    philo->last_meal = get_time();
    pthread_mutex_unlock(&table->dead_mutex);
    print_action(philo, "is eating");
    smart_sleep(table->time_to_die, philo->table);
	pthread_mutex_lock(&table->dead_mutex);
    philo->eaten_meals++;
	pthread_mutex_unlock(&table->dead_mutex);
    pthread_mutex_unlock(second);
    pthread_mutex_unlock(first);
    return (1);
}
static int  philo_check_running(t_philo *philo)
{
	int	running;
	t_table *table;
	
	table = philo->table;
	pthread_mutex_lock(&philo->table->dead_mutex);
	if (table->dead || table->all_ate)
		running = 0;
	else
		running = 1;
	pthread_mutex_unlock(&philo->table->dead_mutex);
	return (running);
}

void	*phroutine(void *arg)
{
	t_philo			*philo;
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (philo_check_running(philo))
	{
		print_action(philo, "is thinking");
		sort_fork(philo, &first, &second);
		pthread_mutex_lock(first);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(second);
		print_action(philo, "has taken a fork");
		if (!philo_eat(philo, first, second))
			break ;
		print_action(philo, "is sleeping");
		smart_sleep(philo->table->time_to_die, philo->table);
	}
	return (NULL);
}

void	sim_start(t_table *table)
{
	int			i;
	pthread_t	monitor_thread;

	i = 0;
	while (i < table->ph_num)
	{
		if (pthread_create(&table->philos[i].thread, NULL, phroutine,
            &table->philos[i]) != 0)
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
	i = -1;
	while (++i < table->ph_num)
		pthread_join(table->philos[i].thread, NULL);
}
