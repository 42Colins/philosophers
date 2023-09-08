/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rest.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 19:28:49 by cprojean          #+#    #+#             */
/*   Updated: 2023/09/08 18:24:36 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_sleep(t_philo *philo)
{
	// int	index;

	// index = 0;
	// while (index < 1000)
	// {
	// 	pthread_mutex_lock(&philo->data->modif);
	// 	if ((philo->data->nbr_of_dinner != -1 && \
	// 		(philo->data->done_dinners >= philo->data->nbr_of_dinner)) || \
	// 		(philo->data->death == DEAD) || (is_anyone_dead(philo) == DEAD))
	// 	{
	// 		pthread_mutex_unlock(&philo->data->modif);
	// 		return (-1);
	// 	}
	// 	pthread_mutex_unlock(&philo->data->modif);
	// 	usleep(philo->data->sleep_time);
	// 	index++;
	// }
	if (ft_usleep(philo, philo->data->sleep_time) == -1)
		return (-1);
	return (0);
}

int	ft_usleep(t_philo *philo, int	rest)
{
	long	start_time;
	long	tmp;
	
	tmp = 0;
	start_time = ft_get_time();
	while (tmp < start_time + (rest))
	{
		pthread_mutex_lock(&philo->data->modif);
		if ((philo->data->nbr_of_dinner != -1 && \
			(philo->data->done_dinners >= philo->data->nbr_of_dinner)) || \
			(philo->data->death == DEAD))
		{
			pthread_mutex_unlock(&philo->data->modif);
			return (-1);
		}
		pthread_mutex_unlock(&philo->data->modif);
		tmp = ft_get_time();
		// usleep(200);
	}
	// printf("start : %ld, tmp : %ld, rest : %d\n", start_time, tmp, rest);
	return (0);
}
