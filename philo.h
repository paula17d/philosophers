/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauladrettas <pauladrettas@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:32:19 by pdrettas          #+#    #+#             */
/*   Updated: 2025/05/22 20:31:53 by pauladretta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define MSG_INPUT "input example: [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [optional: number_of_times_each_philosopher_must_eat]\n"
# define ERR_ARGS "error: invalid number of arguments.\n"
# define ERR_PHILOS "error: too many philosophers (> 200).\n"
# define ERR_NUM "error: arguments must contain only numeric digits (0–9) and represent positive values.\n"
# define ERR_NUM_MAX "error: argument too large. maximum allowed is 2,147,483,647.\n"

typedef struct data_s
{
	long			start_time;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	pthread_mutex_t	print;
	pthread_mutex_t	time;
	bool			stop_simulation;
	int				meals_completed;
}					t_data;

typedef struct philo_s
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*left_fork_neighbor;
	pthread_mutex_t	right_fork_own;
	t_data			*data;
	long			time_of_eating;
}					t_philo;

bool				parse_input(int argc, char **argv);
long				ft_atoi(const char *str);
void				*routine(void *arg);
bool				run_simulation(t_data *data, t_philo *philo);
void				init_structs(int argc, char **argv, t_data *data,
						t_philo *philo);
void				init_mutex(t_data *data, t_philo *philo);
void				destroy_mutex(t_data *data, t_philo *philo);
t_philo				*init_philos(t_data *data);
t_data				*init_data(int argc, char **argv);
long				get_timestamp_in_ms(void);
void				ft_usleep(long millsec);
int					ft_strcmp(const char *s1, const char *s2);
void				free_all(t_data *data, t_philo *philos, char **argv);
void				print_message(char *msg, t_philo *philo, t_data *data);

// routine
void	take_forks(t_philo *philo, t_data *data);
void	eat(t_philo *philo, t_data *data);
void	put_down_forks(t_philo *philo);
void	get_sleep(t_philo *philo, t_data *data);
void	think(t_philo *philo, t_data *data);

// death monitor
bool	monitor_all_philos(t_philo *philos, t_data *data);
bool    death_monitor(t_philo *philo, t_data *data);
bool	get_stop_simulation_value(t_data *data);

#endif
