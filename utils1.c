/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 12:05:19 by dlima             #+#    #+#             */
/*   Updated: 2024/01/09 14:51:07 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	threads_join(t_philo *philos, int nbr_philos)
{
	int	i;

	i = 0;
	while (i < nbr_philos)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
		{
			perror("failed to join thread");
		}
		i++;
	}
}
void	mutex_destroy(pthread_mutex_t *forks, t_data *data, int fork_nbr, t_philo *philos)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->dead_mutex);
	pthread_mutex_destroy(&data->write_mutex);
	while (i < fork_nbr)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	i = 0;
	while (i < fork_nbr)
	{
		pthread_mutex_destroy(&philos[i].meals_eaten_mutex);
		pthread_mutex_destroy(&philos[i].last_meal_mutex);
		i++;
	}
}
int	get_dead_flag_val(t_data *data)
{
	int	dead_flag_val;

	pthread_mutex_lock(&data->dead_mutex);
	dead_flag_val = data->dead_flag;
	pthread_mutex_unlock(&data->dead_mutex);
	return (dead_flag_val);
}
