/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 11:49:12 by dlima             #+#    #+#             */
/*   Updated: 2024/01/05 17:54:20 by dlima            ###   ########.fr       */
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
	int	finish_simulation;
} t_data;

typedef struct s_philo
{
	int	id;
	pthread_t	thread;
	int	meals_eaten;
	long long	last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_mutex;
	t_data	*data;
} t_philo;


//init.c
void	data_init(int argc, char **argv, t_data *data);
void	philos_init(t_philo *philos, t_data *data);
void	forks_init(t_philo *philos,  pthread_mutex_t *forks, int fork_nbr);

//utils.c
long long getCurrentTimeMillis();
long long get_time_interval(long long start_time);

int		ft_atoi(const char *str);

#endif
