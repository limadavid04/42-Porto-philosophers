/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 12:05:19 by dlima             #+#    #+#             */
/*   Updated: 2024/01/10 15:47:23 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(pthread_mutex_t *fork, t_philo *philo)
{
	pthread_mutex_lock(fork);
	print_msg("has taken a fork\n", philo, 1);
}
void	release_fork(pthread_mutex_t *fork)
{
	pthread_mutex_unlock(fork);
}
void	print_msg(const char *msg,  t_philo *philo, int check_if_dead)
{
	pthread_mutex_t	*write;
	int				id;
	long long 		time;

	id = philo->id;
	write = &philo->data->write_mutex;
	time = get_time_interval(philo->data->start_time);
	if (check_if_dead == 1)
	{
		if (get_dead_flag_val(philo->data) == 1)
			return ;
	}
	pthread_mutex_lock(write);
	printf("%lld %d ", time, id + 1);
	printf("%s", msg);
	pthread_mutex_unlock(write);
}
