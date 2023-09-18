/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 19:30:20 by cprojean          #+#    #+#             */
/*   Updated: 2023/09/18 15:39:08 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_anyone_dead(t_philo *philo)
{
	long			time;

	if ((philo->data->nbr_of_dinner != -1 && \
		(philo->data->done_dinners == philo->data->nbr_of_philos)) || \
		(philo->data->death == DEAD))
		return (DEAD);
	if (philo->last_meal == 0)
		philo->last_meal = philo->creation_time;
	time = ft_get_time();
	if ((time - philo->last_meal) > philo->data->death_timer)
	{
		philo->alive = DEAD;
		philo->data->death = DEAD;
		return (DEAD);
	}
	return (ALIVE);
}

int	do_i_have_time(t_philo *philo, int mode)
{
	struct timeval	checktv;
	long			t;
	int				time;

	if (mode == 0)
		time = philo->data->eat_time;
	else
		time = philo->data->sleep_time;
	if (gettimeofday(&checktv, NULL) == -1)
		return (DEAD);
	t = (checktv.tv_usec * 0.001 + checktv.tv_sec * 1000);
	if (philo->last_meal == 0)
		philo->last_meal = philo->creation_time;
	pthread_mutex_lock(&philo->data->modif);
	if ((philo->data->nbr_of_dinner != -1 && \
		(philo->data->done_dinners == philo->data->nbr_of_philos)))
		return (pthread_mutex_unlock(&philo->data->modif), DEAD);
	pthread_mutex_unlock(&philo->data->modif);
	if ((t - philo->last_meal + time) > philo->data->death_timer)
	{
		usleep((philo->data->death_timer - (t - philo->last_meal)) * 1000);
		kill_philo(philo);
		return (philo->alive = DEAD, DEAD);
	}
	return (ALIVE);
}

void	kill_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->modif);
	philo->data->death = 1;
	pthread_mutex_unlock(&philo->data->modif);
}
