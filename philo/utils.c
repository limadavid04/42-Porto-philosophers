/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 12:27:08 by dlima             #+#    #+#             */
/*   Updated: 2024/01/12 11:23:08 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	nbr;
	int	signal;

	signal = 1;
	nbr = 0;
	i = 0;
	while (((str[i] >= 8 && str[i] <= 13) || str[i] == 32) && str[i])
		i++;
	if (str[i] == '-')
	{
		signal = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		nbr = nbr * 10 + (str[i] - 48);
		i++;
	}
	return (nbr * signal);
}

long long	get_current_time_millis(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((long long)current_time.tv_sec * 1000 + \
	current_time.tv_usec / 1000);
}

long long	get_time_interval(long long start_time)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (((long long)current_time.tv_sec * 1000 + \
	current_time.tv_usec / 1000) - start_time);
}

void	ft_usleep(size_t milliseconds, t_philo *philo)
{
	size_t	start;

	(void)philo;
	start = get_current_time_millis();
	while (((get_current_time_millis() - start) < milliseconds) \
	&& get_dead_flag_val(philo->data) != 1)
		usleep(500);
}

void	mutex_destroy(pthread_mutex_t *forks, t_data *data, \
int fork_nbr, t_philo *philos)
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
