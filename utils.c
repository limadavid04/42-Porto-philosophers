/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlima <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 12:27:08 by dlima             #+#    #+#             */
/*   Updated: 2024/01/03 12:33:45 by dlima            ###   ########.fr       */
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
