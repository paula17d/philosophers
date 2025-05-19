#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

# define MSG_INPUT "input example: [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [optional: number_of_times_each_philosopher_must_eat]\n"
# define ERR_ARGS "error: invalid number of arguments.\n"
# define ERR_PHILOS "error: too many philosophers (> 200).\n"
# define ERR_NUM "error: arguments must contain only numeric digits (0–9) and represent positive values.\n"
# define ERR_NUM_MAX "error: argument too large. maximum allowed is 2,147,483,647.\n"

typedef struct data_s
{	
	long start_time;
	int number_of_philosophers;
	int time_to_die; 
	int time_to_eat;
	int time_to_sleep;
	int number_of_times_each_philosopher_must_eat;
	pthread_mutex_t print;
	pthread_mutex_t time;
	pthread_mutex_t test;
	// pthread_mutex_t meals; // the more mutexes, the more delay bc have to wait here and there again (one entire mutex is better (one wait each not multiple) -> TODO: fix)
	bool death_of_philo; // true or false
	int meals_completed;
} t_data;

typedef struct philo_s
{
	int id;
	pthread_t thread; 
	pthread_mutex_t  *left_fork_neighbor;
	pthread_mutex_t  right_fork_own;
	t_data *data;
	long time_since_eating;
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
long get_timestamp_in_ms(void);
void ft_usleep(long millsec);
int	ft_strcmp(const char *s1, const char *s2);
void put_down_forks(t_philo	*philo);

#endif


// TODO: timing fix (needs to show big in visualizer)
// TODO: add colors in output for each action (like in visualizer)