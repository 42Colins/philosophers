/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 19:30:20 by cprojean          #+#    #+#             */
/*   Updated: 2023/09/02 23:25:17 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

int	is_anyone_dead(t_philo *philo)
{
	int				index;
	struct timeval	checktv;
	long			time;

	if (gettimeofday(&checktv, NULL) == -1)
		return (DEAD);
	time = (checktv.tv_usec * 0.001 + checktv.tv_sec * 1000);
	index = 0;
	if ((philo->data->nbr_of_dinner != -1 && (philo->data->done_dinners >= philo->data->nbr_of_dinner)) || \
		(philo->data->death == DEAD))
		return (DEAD);
	if (philo->last_meal == 0)
		philo->last_meal = philo->creation_time;
	while (index++ < philo->data->nbr_of_philos)
	{
		if (((time - philo->last_meal) >= philo->data->death_timer))
		{
			// printf("%d\n", philo->data->done_dinners);
			philo->alive = DEAD;
			return (DEAD);
		}
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
	if ((philo->data->nbr_of_dinner != -1 && (philo->data->done_dinners >= philo->data->nbr_of_dinner)))
		return (DEAD);
	// printf("death  + last meal: %ld, time + t : %ld\n", philo->last_meal + philo->data->death_timer, t);
	if ((t - philo->last_meal + time) >= philo->data->death_timer)
	{
		// printf("t - last meal + t : %ld , death : %d, calc : %ld\n", (t - philo->last_meal + time), philo->data->death_timer, (t - philo->last_meal + time) - philo->data->death_timer);
		if (t - philo->last_meal > philo->data->death_timer)
			return (ALIVE);
		usleep((philo->data->death_timer - (t - philo->last_meal)) * 1000);
		philo->data->death = 1;
		philo->alive = DEAD;
		// printf("%d\n", philo->data->done_dinners);
		return (DEAD);
	}
	return (ALIVE);
}
