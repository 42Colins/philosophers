/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 19:29:30 by cprojean          #+#    #+#             */
/*   Updated: 2023/09/02 23:12:47 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	search_fork(t_philo *philo, int num);
static int	take_fork(t_philo *philo, int num, int oldnum);

int	freud(t_philo *philo, int num)
{
	pthread_mutex_lock(&philo->data->modif);
	if ((philo->data->nbr_of_dinner != -1 && (philo->data->done_dinners >= philo->data->nbr_of_dinner)) || \
		(philo->data->death == DEAD) || (is_anyone_dead(philo) == DEAD))
	{
		pthread_mutex_unlock(&philo->data->modif);
		return (-1);
	}
	pthread_mutex_unlock(&philo->data->modif);
	if (search_fork(philo, num) == -1)
		return (-1);
	return (0);
}

static int	search_fork(t_philo *philo, int num)
{
	int	left_num;

	if (philo->num == 1)
		left_num = philo->data->nbr_of_philos - 1;
	else
		left_num = num - 1;
	if (take_fork(philo, num, -1) == -1)
		return (-1);
	if (take_fork(philo, left_num, num) == -1)
		return (-1);
	return (0);
}

static int	take_fork(t_philo *philo, int num, int oldnum)
{
	while (1)
	{
		pthread_mutex_lock(&philo->data->modif);
		if ((philo->data->nbr_of_dinner != -1 && (philo->data->done_dinners >= philo->data->nbr_of_dinner)) || \
			(philo->data->death == DEAD) || (is_anyone_dead(philo) == DEAD))
		{
			if (oldnum != -1 && philo->data->forks[oldnum] != FREE)
				philo->data->forks[oldnum] = FREE;
			pthread_mutex_unlock(&philo->data->modif);
			return (-1);
		}
		if (philo->data->forks[num] == FREE)
		{
			pthread_mutex_unlock(&philo->data->modif);
			pthread_mutex_lock(&philo->data->forchetta[num]);
			philo->data->forks[num] = USED;
			pthread_mutex_unlock(&philo->data->forchetta[num]);
			break ;
		}
		pthread_mutex_unlock(&philo->data->modif);
	}
	print_timestamp(philo, NULL);
	return (0);
}
