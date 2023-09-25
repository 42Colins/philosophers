/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_timestamp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 19:38:13 by cprojean          #+#    #+#             */
/*   Updated: 2023/09/25 20:22:56 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	next_print_timestamp(t_philo *philo, int value, long time);
static int	next_next_print_timestamp(t_philo *philo, int value, long time);
static int	final_print_timestamp(t_philo *philo, int value);

int	print_timestamp(t_philo *philo, int value)
{
	long			time;

	time = 0;
	if (value == DEATH && philo->data->count == 0)
	{
		ft_print(DYING, philo);
		pthread_mutex_lock(&philo->data->modif);
		philo->data->count = 1;
		pthread_mutex_unlock(&philo->data->modif);
		return (0);
	}
	else
		return (pthread_mutex_unlock(&philo->data->modif), \
				next_print_timestamp(philo, value, time));
}

static int	next_print_timestamp(t_philo *philo, int value, long time)
{
	if (value == SLEEP)
	{
		if (is_dead(philo) == DEAD)
			return (DEAD);
		time = ft_get_time();
		if (do_i_have_time(philo, 1) == DEAD)
			return (-1);
		ft_print(SLEEPING, philo);
		return (0);
	}
	return (next_next_print_timestamp(philo, value, time));
}

static int	next_next_print_timestamp(t_philo *philo, int value, long time)
{
	if (value == EAT)
	{
		if (is_dead(philo) == DEAD)
			return (DEAD);
		time = ft_get_time();
		philo->last_meal = time;
		if (do_i_have_time(philo, 0) == DEAD)
			return (DEAD);
		ft_print(EATING, philo);
	}
	else
		return (final_print_timestamp(philo, value));
	return (0);
}

static int	final_print_timestamp(t_philo *philo, int value)
{
	if (value == THINK)
	{
		if (is_dead(philo) == DEAD)
			return (DEAD);
		ft_print(THINKING, philo);
	}
	else
	{
		if (is_dead(philo) == DEAD)
			return (DEAD);
		ft_print(FORKING, philo);
	}
	return (0);
}

long	ft_get_time(void)
{
	struct timeval	checktv;
	long			time;

	if (gettimeofday(&checktv, NULL) == -1)
		return (-1);
	time = (checktv.tv_usec * 0.001 + checktv.tv_sec * 1000);
	return (time);
}

void	ft_print(char *str, t_philo *philo)
{
	long	time;
	long	tmp;

	time = ft_get_time();
	tmp = time - philo->creation_time;
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->count == 1)
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	pthread_mutex_lock(&philo->data->print);
	printf(str, tmp, philo->num);
	pthread_mutex_unlock(&philo->data->print);
}
