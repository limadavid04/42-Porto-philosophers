/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:19:26 by dlima             #+#    #+#             */
/*   Updated: 2024/01/10 15:25:00 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_dead_flag_val(t_data *data)
{
	int	dead_flag_val;

	pthread_mutex_lock(&data->dead_mutex);
	dead_flag_val = data->dead_flag;
	pthread_mutex_unlock(&data->dead_mutex);
	return (dead_flag_val);
}
static int	check_starvation(t_philo *philo)
{
	long long	time_to_die;
	long long	interval;

	time_to_die = philo->data->time_to_die;
	pthread_mutex_lock(&philo->last_meal_mutex);
	interval = getCurrentTimeMillis() - philo->last_meal;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	if (interval > time_to_die)
		return (1);
	return (0);
}
static int	check_if_dead(t_philo *philo)
{
	pthread_mutex_t	*dead_mutex;
	dead_mutex = &philo->data->dead_mutex;
	if (check_starvation(philo) == 1)
	{
		pthread_mutex_lock(dead_mutex);
		philo->data->dead_flag = 1;
		pthread_mutex_unlock(dead_mutex);
		print_msg("died\n", philo, 0);
		return (1);
	}
	return (0);
}

void	monitor_philos(t_philo *philos, t_data *data)
{
	int	i;
	int	nbr_philos;
	int	ate_min_meals;
	int	min_meals;

	nbr_philos = data->nbr_philos;
	min_meals = data->meal_minimum;
	while (1)
	{
		ate_min_meals = 0;
		i = 0;
		while (i < nbr_philos && check_if_dead(&philos[i]) != 1)
		{
			pthread_mutex_lock(&philos[i].meals_eaten_mutex);
			if (philos[i].meals_eaten >= min_meals)
				ate_min_meals++;
			pthread_mutex_unlock(&philos[i].meals_eaten_mutex);
			i++;
		}
		if (get_dead_flag_val(data) == 1)
			break ;
		if (ate_min_meals == nbr_philos && min_meals != 0)
		{
			pthread_mutex_lock(&data->dead_mutex);
			data->dead_flag = 1;
			pthread_mutex_unlock(&data->dead_mutex);
			break ;
		}
	}
}
