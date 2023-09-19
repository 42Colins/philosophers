/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 19:28:36 by cprojean          #+#    #+#             */
/*   Updated: 2023/09/19 13:10:57 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	devourer(t_philo *philo, int num)
{
	int	tmp;

	if (num + 1 == philo->data->nbr_of_philos)
		tmp = 0;
	else
		tmp = num + 1;
	pthread_mutex_lock(&philo->data->modif);
	if (philo->data->forks[num] != FREE)
		philo->data->forks[num] = FREE;
	if (philo->data->forks[tmp] != FREE)
		philo->data->forks[tmp] = FREE;
	philo->nbr_of_meals += 1;
	if ((philo->data->nbr_of_dinner != -1 && \
		(philo->data->done_dinners == philo->data->nbr_of_philos)) || \
		(philo->data->death == DEAD))
		return (pthread_mutex_unlock(&philo->data->modif), -1);
	if ((philo->nbr_of_meals == philo->data->nbr_of_dinner) && \
		philo->done == 0)
	{
		philo->data->done_dinners += 1;
		philo->done = 1;
	}
	return (pthread_mutex_unlock(&philo->data->modif), 0);
}
