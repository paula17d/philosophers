#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#ifndef MAX_PHILOS
# define MAX_PHILOS 200
#endif


/*
PHILO STRUCT
- last_meal_time
- personal ID (ranging from 1 to number_of_philosophers)
- last_sleep_time (these are to print in terminal line)
- last_think_time (these are to print in terminal line)

MAIN DATA STRUCT
- number_of_philosophers 
- time_to_die
- time_to_eat
- time_to_sleep
- number_of_times_each_philosopher_must_eat (optional argument but do it)
-->  If all philosophers have eaten at least number_of_times_each_philosopher_must_eat
times, the simulation stops. If not specified, the simulation stops when a philosopher dies.
--> include a death_flag ?
*/

typedef struct philo_s
{
	int ID;
	pthread_t thread_philo[200];
	struct data_s *data;
	int left_fork;
	int right_fork;
} t_philo;

typedef struct data_s
{	
	int number_of_philosophers;
	int time_to_die; // TODO: replace int 
	int time_to_eat;
	int time_to_sleep;
	int number_of_times_each_philosopher_must_eat;
	pthread_mutex_t forks[MAX_PHILOS]; // One mutex per fork
} t_data;

bool parse_input(int argc, char **argv);
long ft_atoi(const char *str);
void *routine(void *arg);
bool create_threads(t_data *data, t_philo *philo);
void init_structs(int argc, char **argv, t_data *data, t_philo *philo);
void init_mutex(t_data *data, t_philo *philo);
void destroy_mutex(t_data *data, t_philo *philo);

#endif
