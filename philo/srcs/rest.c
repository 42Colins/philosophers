/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rest.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 19:28:49 by cprojean          #+#    #+#             */
/*   Updated: 2023/09/14 23:27:41 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_sleep(t_philo *philo)
{
	if (ft_usleep(philo, philo->data->sleep_time) == -1)
		return (-1);
	return (0);
}

int	ft_usleep(t_philo *philo, int rest)
{
	long	start_time;
	long	tmp;

	start_time = ft_get_time();
	tmp = start_time;
	while (start_time - tmp < (rest))
	{
		tmp = ft_get_time();
		if (tmp >= start_time + rest)
			break ;
		pthread_mutex_lock(&philo->data->modif);
		if ((philo->data->nbr_of_dinner != -1 && \
			(philo->data->done_dinners == philo->data->nbr_of_philos)) || \
			(philo->data->death == DEAD))
		{
			pthread_mutex_unlock(&philo->data->modif);
			return (-1);
		}
		pthread_mutex_unlock(&philo->data->modif);
		usleep(200);
		tmp = ft_get_time();
	}
	return (0);
}
