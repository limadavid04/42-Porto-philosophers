/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:50:19 by dlima             #+#    #+#             */
/*   Updated: 2024/01/05 18:02:54 by dlima            ###   ########.fr       */
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

void	print_msg(const char *msg,  t_philo *philo)
{
	pthread_mutex_t	*write;
	int				id;
	long long 		time;

	id = philo->id;
	write = &philo->data->write_mutex;
	time = get_time_interval(philo->data->start_time);
	pthread_mutex_lock(write);
	printf("%lld %d ", time, id);
	printf("%s", msg);
	pthread_mutex_unlock(write);
}
void	eat(t_philo *philo)
{
	int	id;

	id = philo->id;

	if (id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_msg("has taken a fork\n", philo);
		pthread_mutex_lock(philo->right_fork);
		print_msg("is_eating\n", philo);
		philo->last_meal = getCurrentTimeMillis();
		usleep(philo->data->time_to_eat * 1000);
		pthread_mutex_lock(&philo->meal_mutex);
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->meal_mutex);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_msg("has taken a fork\n", philo);
		pthread_mutex_lock(philo->left_fork);
		print_msg("is eating\n", philo);
		philo->last_meal = getCurrentTimeMillis();
		usleep(philo->data->time_to_eat * 1000);
		pthread_mutex_lock(&philo->meal_mutex);
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->meal_mutex);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}
int	check_starvation(t_philo *philo)
{
	long long	time_to_die;
	time_to_die = philo->data->time_to_die;
	if (get_time_interval(philo->last_meal) > time_to_die)
		return (1);
	return (0);
}
void	*philo_cycle(void *philo)
{
	pthread_mutex_t	*dead_mutex;
	t_philo			*cur_philo;

	cur_philo = (t_philo *)philo;
	dead_mutex = &cur_philo->data->dead_mutex;
	while (1)
	{
		pthread_mutex_lock(dead_mutex);
		if (cur_philo->data->finish_simulation == 1)
		{
			pthread_mutex_unlock(dead_mutex);
			break ;
		}
		if (check_starvation(cur_philo) == 1)
		{
			pthread_mutex_lock(dead_mutex);
			cur_philo->data->finish_simulation = 1;
			print_msg("died\n", cur_philo);
			pthread_mutex_unlock(dead_mutex);
			break ;
		}
		eat(cur_philo);
		print_msg("is sleeping\n", cur_philo);
		usleep(cur_philo->data->time_to_sleep * 1000);
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
		pthread_mutex_destroy(&philos[i].meal_mutex);
		i++;
	}
}
void	monitor_philos(t_philo *philos, t_data *data)
{
	int	i;
	int	nbr_philos;
	int	ate_min_meals;


	nbr_philos = data->nbr_philos;
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&data->dead_mutex);
		if (data->finish_simulation == 1)
		{
			pthread_mutex_unlock(&data->dead_mutex);
			break ;
		}
		ate_min_meals = 0;
		while (i < nbr_philos)
		{
			pthread_mutex_lock(&philos[i].meal_mutex);
			if (philos[i].meals_eaten >= data->meal_minimum)
				ate_min_meals++;
			pthread_mutex_unlock(&philos[i].meal_mutex);
			i++;
		}
		if (ate_min_meals == data->nbr_philos)
		{
			pthread_mutex_lock(&data->dead_mutex);
			data->finish_simulation = 1;
			pthread_mutex_unlock(&data->dead_mutex);
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
	threads_join(philos, data.nbr_philos);
	mutex_destroy(forks, &data, data.nbr_philos, philos);
	free(philos);
	free(forks);
}
