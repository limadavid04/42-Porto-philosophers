/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:50:19 by dlima             #+#    #+#             */
/*   Updated: 2024/01/03 12:37:20 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


// int	check_input(int argc, char **argv)
// {
// //
// }


void	*philo_cycle(void *philo)
{
	// pthread_mutex_t	*dead;
	pthread_mutex_t	*write;
	t_philo *cur_philo;

	cur_philo = (t_philo *)philo;
	// dead = &philo->data->dead;
	write = &cur_philo->data->write_mutex;

	pthread_mutex_lock(write);
	printf("hello from %d\n", cur_philo->id);
	pthread_mutex_unlock(write);
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
void	mutex_destroy(pthread_mutex_t *forks, t_data *data, int fork_nbr)
{
	int				i;

	i = 0;
	pthread_mutex_destroy(&data->dead);
	pthread_mutex_destroy(&data->write_mutex);
	while (i < fork_nbr)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
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
	mutex_destroy(forks, &data, data.nbr_philos);
	free(philos);
	free(forks);
}
