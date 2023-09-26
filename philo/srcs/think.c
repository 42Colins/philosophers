/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 19:29:30 by cprojean          #+#    #+#             */
/*   Updated: 2023/09/26 12:34:35 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	search_fork(t_philo *philo, int num);
static int	take_fork(t_philo *philo, int num, int oldnum);

int	freud(t_philo *philo, int num)
{
	if (is_dead(philo) == DEAD)
		return (-1);
	if (search_fork(philo, num) == -1)
		return (-1);
	return (0);
}

static int	search_fork(t_philo *philo, int num)
{
	int	right_num;

	if (philo->num == philo->data->nbr_of_philos)
		right_num = 0;
	else
		right_num = num + 1;
	if (take_fork(philo, num, -1) == DEAD)
		return (-1);
	if (take_fork(philo, right_num, num) == DEAD)
		return (-1);
	return (0);
}

static int	take_fork(t_philo *philo, int num, int oldnum)
{
	while (1)
	{
		if (is_dead(philo) == DEAD)
		{
			if (oldnum != -1 && philo->data->forks[oldnum] != FREE)
				philo->data->forks[oldnum] = FREE;
			return (DEAD);
		}
		pthread_mutex_lock(&philo->data->modif);
		if (philo->data->forks[num] == FREE)
		{
			pthread_mutex_unlock(&philo->data->modif);
			pthread_mutex_lock(&philo->data->forchetta[num]);
			philo->data->forks[num] = USED;
			pthread_mutex_unlock(&philo->data->forchetta[num]);
			break ;
		}
		pthread_mutex_unlock(&philo->data->modif);
		usleep(100);
	}
	print_timestamp(philo, FORK);
	return (0);
}
