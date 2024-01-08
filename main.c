/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:50:19 by dlima             #+#    #+#             */
/*   Updated: 2024/01/08 17:00:32 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


// int	check_input(int argc, char **argv)
// {
// //
// }
// ◦ timestamp_in_ms X has taken a fork
// ◦ timestamp_in_ms X is eating
// ◦ timestamp_in_ms X is sleeping
// ◦ timestamp_in_ms X is thinking
// ◦ timestamp_in_ms X died

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = getCurrentTimeMillis();
	while ((getCurrentTimeMillis() - start) < milliseconds)
		usleep(500);
	return (0);
}
void	eat(t_philo *philo)
{
	int	id;

	id = philo->id;

	if (id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		if (get_dead_flag_val(philo->data) == 1)
			return ;
		print_msg("has taken a fork\n", philo);
		pthread_mutex_lock(philo->right_fork);
		if (get_dead_flag_val(philo->data) == 1)
			return ;
		print_msg("has taken a fork\n", philo);
		if (get_dead_flag_val(philo->data) == 1)
		{
			// pthread_mutex_unlock(philo->left_fork);
			// pthread_mutex_unlock(philo->right_fork);
			return ;
		}
		pthread_mutex_lock(&philo->meal_mutex);
		philo->last_meal = getCurrentTimeMillis();
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->meal_mutex);
		print_msg("is eating\n", philo);
		ft_usleep(philo->data->time_to_eat);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		if (get_dead_flag_val(philo->data) == 1)
			return ;
		print_msg("has taken a fork\n", philo);
		pthread_mutex_lock(philo->left_fork);
		if (get_dead_flag_val(philo->data) == 1)
			return ;
		print_msg("has taken a fork\n", philo);
		if (get_dead_flag_val(philo->data) == 1)
		{
			// pthread_mutex_unlock(philo->right_fork);
			// pthread_mutex_unlock(philo->left_fork);
			return ;
		}
		pthread_mutex_lock(&philo->meal_mutex);
		philo->last_meal = getCurrentTimeMillis();
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->meal_mutex);
		print_msg("is eating\n", philo);
		ft_usleep(philo->data->time_to_eat);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}

void	*philo_cycle(void *philo)
{
	// pthread_mutex_t	*dead_mutex;
	t_philo			*cur_philo;
	// int				meal_minimum;
	cur_philo = (t_philo *)philo;
	// dead_mutex = &cur_philo->data->dead_mutex;
	while (1)
	{
		if (get_dead_flag_val(cur_philo->data) == 1)
			break ;
		eat(cur_philo);
		if (get_dead_flag_val(cur_philo->data) == 1)
			break ;
		print_msg("is sleeping\n", cur_philo);
		ft_usleep(cur_philo->data->time_to_sleep);
		if (get_dead_flag_val(cur_philo->data) == 1)
			break ;
		print_msg("is thinking\n", cur_philo);
	}
	return (NULL);
}

void	threads_init(t_philo *philos, int nbr_philos)
{
	int	i;

	i = 0;
	while (i < nbr_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, &philo_cycle, &philos[i]) != 0)
		{
			perror("failed to create thread");
		}
		i++;
	}
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
		while (i < nbr_philos)
		{
			if (check_if_dead(&philos[i]) == 1)
				break ;
			pthread_mutex_lock(&philos[i].meal_mutex);
			if (philos[i].meals_eaten >= min_meals)
				ate_min_meals++;
			pthread_mutex_unlock(&philos[i].meal_mutex);
			i++;
		}
		if (get_dead_flag_val(data) == 1)
			break ;
		if (ate_min_meals == nbr_philos && min_meals != 0)
		{
			pthread_mutex_lock(&data->dead_mutex);
			data->dead_flag = 1;
			pthread_mutex_lock(&data->dead_mutex);
			break ;
		}
	}
}
int	main(int argc, char **argv)
{
	t_data			data;
	t_philo			*philos;
	pthread_mutex_t	*forks;

	data_init(argc, argv, &data);
	forks = malloc(sizeof(pthread_mutex_t) * data.nbr_philos);
	philos = malloc(sizeof(t_philo) * data.nbr_philos);
	philos_init(philos, &data);
	forks_init(philos, forks,  data.nbr_philos);
	threads_init(philos, data.nbr_philos);
	monitor_philos(philos, &data);
	threads_join(philos, data.nbr_philos);
	mutex_destroy(forks, &data, data.nbr_philos, philos);
	free(philos);
	free(forks);
}
