/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:50:19 by dlima             #+#    #+#             */
/*   Updated: 2024/01/10 15:33:48 by dlima            ###   ########.fr       */
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
