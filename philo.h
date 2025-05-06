#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct data_s
{	
	int number_of_philosophers;
	int time_to_die; 
	int time_to_eat;
	int time_to_sleep;
	int number_of_times_each_philosopher_must_eat;
} t_data;

typedef struct philo_s
{
	int id;
	pthread_t thread; 
	pthread_mutex_t  *left_fork_neighbor;
	pthread_mutex_t  right_fork_own;
	t_data *data;
} t_philo;


bool parse_input(int argc, char **argv);
long ft_atoi(const char *str);
void *routine(void *arg);
bool create_threads(t_data *data, t_philo *philo);
void init_structs(int argc, char **argv, t_data *data, t_philo *philo);
void init_mutex(t_data *data, t_philo *philo);
void destroy_mutex(t_data *data, t_philo *philo);
t_philo *init_philos(t_data *data);
t_data *init_data(int argc, char **argv);

#endif
