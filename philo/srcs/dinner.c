/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 19:28:36 by cprojean          #+#    #+#             */
/*   Updated: 2023/09/19 17:21:23 by cprojean         ###   ########.fr       */
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
	pthread_mutex_unlock(&philo->data->modif);
	philo->nbr_of_meals += 1;
	if (is_dead(philo) == DEAD)
		return (DEAD);
	if ((philo->nbr_of_meals == philo->data->nbr_of_dinner) && \
		philo->done == 0)
	{
		pthread_mutex_lock(&philo->data->modif);
		philo->data->done_dinners += 1;
		pthread_mutex_unlock(&philo->data->modif);
		philo->done = 1;
	}
	return (0);
}
