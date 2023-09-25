/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_timestamp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 19:38:13 by cprojean          #+#    #+#             */
/*   Updated: 2023/09/25 18:21:24 by cprojean         ###   ########.fr       */
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
	// if (is_dead(philo) == DEAD)
	// 	return (DEAD);
	// printf("%d\n", philo->data->count);
	pthread_mutex_lock(&philo->data->modif);
	if (value == DEATH && philo->data->count == 0)
	{
		philo->data->count = 1;
		pthread_mutex_unlock(&philo->data->modif);
		ft_print(value, philo);
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
		ft_print(value, philo);
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
		ft_print(value, philo);
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
		ft_print(value, philo);
	}
	else
	{
		if (is_dead(philo) == DEAD)
			return (DEAD);
		ft_print(value, philo);
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

void	ft_print(int value, t_philo *philo)
{
	long	time;
	long	tmp;
	
	time = ft_get_time();
	tmp = time - philo->creation_time;
	pthread_mutex_lock(&philo->data->mutex);
	if (value == THINK)
		printf("%ld %d is thinking\n", tmp, philo->num);
	else if (value == EAT)
		printf("%ld %d is eating\n", tmp, philo->num);
	else if (value == SLEEP)
		printf("%ld %d is sleeping\n", tmp, philo->num);
	else if (value == DEATH)
		printf("\033[0;31m%ld %d died\n", tmp, philo->num);
	else if (value == FORK)
		printf("%ld %d has taken a fork\n", tmp, philo->num);
	pthread_mutex_unlock(&philo->data->mutex);
}
