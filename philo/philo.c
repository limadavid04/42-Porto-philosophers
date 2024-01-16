/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:50:19 by dlima             #+#    #+#             */
/*   Updated: 2024/01/16 11:19:32 by dlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_positive_int(char *str)
{
	int			i;
	long int	number;

	number = 0;
	i = 0;
	if (str[i] == '-')
		return (0);
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		number = number * 10 + (str[i] - 48);
		i++;
	}
	if (str[i] != '\0')
		return (0);
	if (number >= 0 && number <= 2147483647)
		return (1);
	return (0);
}

int	check_input(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (0);
	while (argc > 1)
	{
		if (!is_positive_int(argv[argc - 1]))
			return (0);
		argc--;
	}
	if (ft_atoi(argv[1]) == 0)
		return (0);
	if (argc == 6 && ft_atoi(argv[5]) == 0)
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_philo			*philos;
	pthread_mutex_t	*forks;

	if (check_input(argc, argv) != 1)
	{
		printf("ERROR: invalid input\n");
		return (EXIT_FAILURE);
	}
	data_init(argc, argv, &data);
	forks = malloc(sizeof(pthread_mutex_t) * data.nbr_philos);
	philos = malloc(sizeof(t_philo) * data.nbr_philos);
	philos_init(philos, &data);
	forks_init(philos, forks, data.nbr_philos);
	threads_init(philos, data.nbr_philos);
	monitor_philos(philos, &data);
	threads_join(philos, data.nbr_philos);
	mutex_destroy(forks, &data, data.nbr_philos, philos);
	free(philos);
	free(forks);
}
