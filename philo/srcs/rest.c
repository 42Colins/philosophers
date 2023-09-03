/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rest.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 19:28:49 by cprojean          #+#    #+#             */
/*   Updated: 2023/09/02 23:09:40 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->modif);
	if ((philo->data->nbr_of_dinner != -1 && (philo->data->done_dinners >= philo->data->nbr_of_dinner)) || \
		(philo->data->death == DEAD))
	{
		pthread_mutex_unlock(&philo->data->modif);
		return (-1);
	}
	pthread_mutex_unlock(&philo->data->modif);
	usleep(philo->data->sleep_time * 1000);
	return (0);
}
