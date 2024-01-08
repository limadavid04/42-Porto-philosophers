/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 12:27:08 by dlima             #+#    #+#             */
/*   Updated: 2024/01/08 17:03:26 by dlima            ###   ########.fr       */
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
long long getCurrentTimeMillis()
{
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);

	return ((long long)currentTime.tv_sec * 1000 + currentTime.tv_usec / 1000);
}
long long get_time_interval(long long start_time)
{
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
	return (((long long)currentTime.tv_sec * 1000 + currentTime.tv_usec / 1000) - start_time);
}
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
int	check_starvation(t_philo *philo)
{
	long long	time_to_die;
	long long	interval;

	time_to_die = philo->data->time_to_die;
	pthread_mutex_lock(&philo->meal_mutex);
	interval = getCurrentTimeMillis() - philo->last_meal;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (interval > time_to_die)
		return (1);
	return (0);
}
int	check_if_dead(t_philo *philo)
{
	pthread_mutex_t	*dead_mutex;
	dead_mutex = &philo->data->dead_mutex;
	if (check_starvation(philo) == 1)
	{
		pthread_mutex_lock(dead_mutex);
		philo->data->dead_flag = 1;
		pthread_mutex_unlock(dead_mutex);
		print_msg("died\n", philo);
		return (1);
	}
	return (0);
}
