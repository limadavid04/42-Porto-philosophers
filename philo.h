/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 11:49:12 by dlima             #+#    #+#             */
/*   Updated: 2024/01/10 15:47:39 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_data
{
	int	nbr_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	meal_minimum;
	long long	start_time;
	// t_philo **philo;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	write_mutex;
	int	dead_flag;
} t_data;

typedef struct s_philo
{
	int	id;
	pthread_t	thread;
	int	meals_eaten;
	long long	last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meals_eaten_mutex;
	pthread_mutex_t	last_meal_mutex;
	t_data	*data;
} t_philo;


//init.c
void		data_init(int argc, char **argv, t_data *data);
void		philos_init(t_philo *philos, t_data *data);
void		forks_init(t_philo *philos,  pthread_mutex_t *forks, int fork_nbr);
void		threads_join(t_philo *philos, int nbr_philos);
void		threads_init(t_philo *philos, int nbr_philos);

//philo_cycle.c
void		*philo_cycle(void *philo);

//philo_monitor.c
void		monitor_philos(t_philo *philos, t_data *data);
int			get_dead_flag_val(t_data *data);

//utils.c
int			ft_atoi(const char *str);
long long	getCurrentTimeMillis();
long long	get_time_interval(long long start_time);
void		ft_usleep(size_t milliseconds, t_philo *philo);
void		mutex_destroy(pthread_mutex_t *forks, t_data *data, int fork_nbr, t_philo *philos);

//utils1.c
void		take_fork(pthread_mutex_t *fork, t_philo *philo);
void		release_fork(pthread_mutex_t *fork);
void		print_msg(const char *msg,  t_philo *philo, int check_if_dead);

#endif
