/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_timestamp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 19:38:13 by cprojean          #+#    #+#             */
/*   Updated: 2023/09/02 23:01:14 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	next_print_timestamp(t_philo *philo, char *str, long time);

int	print_timestamp(t_philo *philo, char *str)
{
	struct timeval	checktv;
	long			time;

	pthread_mutex_lock(&philo->data->mutex);
	if (gettimeofday(&checktv, NULL) == -1)
	{
		pthread_mutex_unlock(&philo->data->mutex);
		return (-1);
	}
	time = (checktv.tv_usec * 0.001 + checktv.tv_sec * 1000);
	if (ft_strncmp(str, "DEATH", ft_strlen(str)) == 0)
		printf("\033[0;31m%ld %d died\n", \
		time - philo->creation_time, philo->num);
	pthread_mutex_unlock(&philo->data->mutex);
	pthread_mutex_lock(&philo->data->modif);
	if (philo->data->death == 1 || (philo->data->done_dinners == philo->data->nbr_of_dinner - 1))
	{
		pthread_mutex_unlock(&philo->data->modif);
		return (-1);
	}
	pthread_mutex_unlock(&philo->data->modif);
	if (ft_strncmp(str, "SLEEP", ft_strlen(str)) == 0)
	{
		pthread_mutex_lock(&philo->data->modif);
		if (do_i_have_time(philo, 1) == DEAD)
		{
			pthread_mutex_unlock(&philo->data->modif);
			return (-1);
		}
		pthread_mutex_unlock(&philo->data->modif);
		pthread_mutex_lock(&philo->data->mutex);
		printf("%ld %d is sleeping\n", time - philo->creation_time, philo->num);
		pthread_mutex_unlock(&philo->data->mutex);
	}
	return (next_print_timestamp(philo, str, time));
}

static int	next_print_timestamp(t_philo *philo, char *str, long time)
{
	if (ft_strncmp(str, "EAT", ft_strlen(str)) == 0)
	{
		pthread_mutex_lock(&philo->data->modif);
		if (do_i_have_time(philo, 0) == DEAD)
		{
			pthread_mutex_unlock(&philo->data->modif);
			return (-1);
		}
		pthread_mutex_unlock(&philo->data->modif);
		pthread_mutex_lock(&philo->data->mutex);
		printf("\033[0;35m%ld %d is eating\033[0m\n", time - philo->creation_time, philo->num);
		pthread_mutex_unlock(&philo->data->mutex);
		philo->last_meal = time;
	}
	else
	{
		pthread_mutex_lock(&philo->data->mutex);
		if (ft_strncmp(str, "THINK", ft_strlen(str)) == 0)
			printf("%ld %d is thinking\n", time - philo->creation_time, philo->num);
		else
			printf("%ld %d has taken a fork\n", \
			time - philo->creation_time, philo->num);
		pthread_mutex_unlock(&philo->data->mutex);
	}
	return (0);
}
