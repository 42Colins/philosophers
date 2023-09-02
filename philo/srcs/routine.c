/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 19:29:51 by cprojean          #+#    #+#             */
/*   Updated: 2023/09/02 23:20:02 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	routine(t_philo *philo, int num);

void	handle_philos(t_philo *philo)
{
	int	num;

	num = 0;
	while (1)
	{
		pthread_mutex_lock(&philo->data->modif);
		if ((philo->data->done_dinners >= philo->data->nbr_of_dinner) || \
			(philo->data->death == DEAD) || is_anyone_dead(philo) == DEAD)
		{
			pthread_mutex_unlock(&philo->data->modif);
			break ;
		}
		pthread_mutex_unlock(&philo->data->modif);
		routine(philo, num);
		pthread_mutex_lock(&philo->data->modif);
		if (philo->nbr_of_meals == philo->data->nbr_of_philos - 1)
		{
			philo->data->done_dinners += 1;
			philo->nbr_of_meals = 0;
		}
		pthread_mutex_unlock(&philo->data->modif);
	}
	if (philo->alive == DEAD)
		print_timestamp(philo, "DEATH");
}

static void	routine(t_philo *philo, int num)
{
	num = philo->num - 1;
	if (print_timestamp(philo, "THINK") == -1)
		return ;
	if (freud(philo, num) == -1)
		return ;
	if (print_timestamp(philo, "EAT") == -1)
		return ;
	usleep(philo->data->eat_time * 1000);
	if (devourer(philo, num) == -1)
		return ;
	if (print_timestamp(philo, "SLEEP") == -1)
		return ;
	if (ft_sleep(philo) == -1)
		return ;
}
