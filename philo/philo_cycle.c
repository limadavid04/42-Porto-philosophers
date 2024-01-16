/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cycle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:30:54 by dlima             #+#    #+#             */
/*   Updated: 2024/01/12 11:40:55 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_current_time_millis();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	print_msg("is eating\n", philo, 1);
	pthread_mutex_lock(&philo->meals_eaten_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meals_eaten_mutex);
	ft_usleep(philo->data->time_to_eat, philo);
}

static void	eat(t_philo *philo)
{
	int	id;

	id = philo->id;
	if (id % 2 == 0)
	{
		take_fork(philo->left_fork, philo);
		take_fork(philo->right_fork, philo);
		philo_eat(philo);
		release_fork(philo->left_fork);
		release_fork(philo->right_fork);
	}
	else
	{
		take_fork(philo->right_fork, philo);
		take_fork(philo->left_fork, philo);
		philo_eat(philo);
		release_fork(philo->right_fork);
		release_fork(philo->left_fork);
	}
}

static void	*handle_one_philo(t_philo *philo)
{
	take_fork(philo->right_fork, philo);
	release_fork(philo->right_fork);
	return (NULL);
}

void	*philo_cycle(void *philo)
{
	t_philo			*cur_philo;

	cur_philo = (t_philo *)philo;
	if (cur_philo->data->nbr_philos == 1)
		return (handle_one_philo(cur_philo));
	while (get_dead_flag_val(cur_philo->data) != 1)
	{
		eat(cur_philo);
		print_msg("is sleeping\n", cur_philo, 1);
		ft_usleep(cur_philo->data->time_to_sleep, cur_philo);
		print_msg("is thinking\n", cur_philo, 1);
		usleep(500);
	}
	return (NULL);
}
