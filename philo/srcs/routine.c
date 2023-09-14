/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 19:29:51 by cprojean          #+#    #+#             */
/*   Updated: 2023/09/14 23:44:45 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	routine(t_philo *philo);

void	handle_philos(t_philo *philo)
{
	philo->done = 0;
	while (1)
	{
		pthread_mutex_lock(&philo->data->modif);
		if ((philo->data->nbr_of_dinner != -1 && \
			(philo->data->done_dinners == philo->data->nbr_of_philos)) || \
			(philo->data->death == DEAD))
		{
			pthread_mutex_unlock(&philo->data->modif);
			break ;
		}
		pthread_mutex_unlock(&philo->data->modif);
		routine(philo);
		pthread_mutex_lock(&philo->data->modif);
		if ((philo->nbr_of_meals == philo->data->nbr_of_dinner) && \
			philo->done == 0)
		{
			philo->data->done_dinners += 1;
			philo->done = 1;
		}
		pthread_mutex_unlock(&philo->data->modif);
	}
	if (philo->alive == DEAD)
		print_timestamp(philo, "DEATH");
}

static void	routine(t_philo *philo)
{
	int	num;

	num = philo->num - 1;
	if (print_timestamp(philo, "THINK") == -1)
		return ;
	if ((philo->last_meal == 0) && philo->num % 2 == 0)
		usleep(100000);
	if (freud(philo, num) == -1)
		return ;
	if (print_timestamp(philo, "EAT") == -1)
		return ;
	if (ft_usleep(philo, philo->data->eat_time) == -1)
		return ;
	if (devourer(philo, num) == -1)
		return ;
	if (print_timestamp(philo, "SLEEP") == -1)
		return ;
	if (ft_sleep(philo) == -1)
		return ;
}
