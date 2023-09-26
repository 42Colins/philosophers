/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 19:29:51 by cprojean          #+#    #+#             */
/*   Updated: 2023/09/26 12:37:55 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	routine(t_philo *philo);

void	handle_philos(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	pthread_mutex_unlock(&philo->mutex);
	philo->done = 0;
	if ((philo->last_meal == 0) && philo->num % 2 == 1)
		usleep(2000);
	while (1)
	{
		if (is_dead(philo) == DEAD)
			break ;
		routine(philo);
	}
	if (philo->alive == DEAD)
	{
		print_timestamp(philo, DEATH);
	}
}

static void	routine(t_philo *philo)
{
	int	num;

	num = philo->num - 1;
	if (print_timestamp(philo, THINK) == -1)
		return ;
	else if (freud(philo, num) == -1)
		return ;
	else if (print_timestamp(philo, EAT) == -1)
		return ;
	else if (ft_usleep(philo, philo->data->eat_time) == -1)
		return ;
	else if (devourer(philo, num) == -1)
		return ;
	else if (print_timestamp(philo, SLEEP) == -1)
		return ;
	else if (ft_sleep(philo) == -1)
		return ;
}
