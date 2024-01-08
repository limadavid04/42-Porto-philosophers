/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:43:02 by dlima             #+#    #+#             */
/*   Updated: 2024/01/08 12:08:51 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	data_init(int argc, char **argv, t_data *data)
{
	data->nbr_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->dead_flag = 0;
	data->meal_minimum = 0;
	if (argc == 6)
		data->meal_minimum = ft_atoi(argv[5]);
	data->start_time = getCurrentTimeMillis();
	pthread_mutex_init(&data->dead_mutex, NULL);
	pthread_mutex_init(&data->write_mutex, NULL);
}
void	philos_init(t_philo *philos, t_data *data)
{
	int	i;
	int	nbr_philos;

	nbr_philos = data->nbr_philos;
	i = 0;
	while (i < nbr_philos)
	{
		philos[i].id = i;
		philos[i].meals_eaten = 0;
		philos[i].last_meal = data->start_time;
		philos[i].data = data;
		pthread_mutex_init(&philos[i].meal_mutex, NULL);
		i++;
	}
}
void	forks_init(t_philo *philos,  pthread_mutex_t *forks, int fork_nbr)
{
	int i;
	int philo_id;

	i = 0;
	while (i < fork_nbr)
	{
		philo_id = philos[i].id;
		philos[i].left_fork = &forks[(philo_id +1) % fork_nbr];
		philos[i].right_fork = &forks[philo_id];
		pthread_mutex_init(philos[i].left_fork, NULL);
		pthread_mutex_init(philos[i].right_fork, NULL);
		i++;
	}
}

