/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 11:49:12 by dlima             #+#    #+#             */
/*   Updated: 2024/01/03 12:35:54 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>

typedef struct s_data
{
	int	nbr_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	meal_minimum;
	long long	start_time;
	// t_philo **philo;
	pthread_mutex_t	dead;
	pthread_mutex_t	write_mutex;
} t_data;

typedef struct s_philo
{
	int	id;
	pthread_t	thread;
	int	meals_eaten;
	int	last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data	*data;
} t_philo;


//init.c
void	data_init(int argc, char **argv, t_data *data);
void	philos_init(t_philo *philos, t_data *data);
void	forks_init(t_philo *philos,  pthread_mutex_t *forks, int fork_nbr);

//utils.c
long long getCurrentTimeMillis();
int		ft_atoi(const char *str);

#endif
