/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rest.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 19:28:49 by cprojean          #+#    #+#             */
/*   Updated: 2023/09/25 16:55:09 by cprojean         ###   ########.fr       */
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
		if (is_dead(philo) == DEAD)
			return (DEAD);
		usleep(200);
		tmp = ft_get_time();
	}
	// printf("%ld , %d\n", tmp - start_time, rest);
	return (0);
}

