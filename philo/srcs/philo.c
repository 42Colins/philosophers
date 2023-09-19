/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 19:36:05 by cprojean          #+#    #+#             */
/*   Updated: 2023/09/18 15:59:19 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	do_philosophers(t_data *data)
{
	int				i;
	pthread_mutex_t	mutex;
	t_philo			*philo;

	pthread_mutex_init(&mutex, NULL);
	i = 0;
	philo = initiate_philos(data, mutex);
	while (i < data->nbr_of_philos)
	{
		if (pthread_create(&philo[i].tid, NULL, \
			(void *)handle_philos, &philo[i]) != 0)
			return ;
		else
			i++;
	}
	i = 0;
	while (i < data->nbr_of_philos)
	{
		pthread_join(philo[i].tid, NULL);
		i++;
	}
	free(philo);
}

void	free_everything(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_of_philos)
	{
		pthread_mutex_destroy(&data->forchetta[i]);
		i++;
	}
	free(data->forchetta);
	free(data->forks);
	free(data);
}

t_philo	*initiate_philos(t_data *data, pthread_mutex_t mutex)
{
	int				index;
	long			time;
	t_philo			*philo;
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (NULL);
	time = (tv.tv_usec * 0.001 + tv.tv_sec * 1000);
	index = 0;
	philo = malloc(sizeof(t_philo) * data->nbr_of_philos);
	if (!philo)
		return (NULL);
	while (index < data->nbr_of_philos)
	{
		philo[index].data = data;
		philo[index].num = index + 1;
		philo[index].creation_time = time;
		philo[index].last_meal = 0;
		philo[index].nbr_of_meals = 0;
		philo[index].alive = ALIVE;
		index++;
	}
	philo->mutex = mutex;
	return (philo);
}

t_data	*handle_parameters(int count, char **values)
{
	int				index;
	pthread_mutex_t	*forks;
	int				*disponibility;
	t_data			*data;

	data = malloc(sizeof(t_data));
	data->nbr_of_philos = ft_atoi(values[1]);
	data->nbr_of_dinner = -1;
	if (count == 4)
		data->nbr_of_dinner = ft_atoi(values[5]);
	data->sleep_time = ft_atoi(values[4]);
	data->eat_time = ft_atoi(values[3]);
	data->death_timer = ft_atoi(values[2]);
	pthread_mutex_init(&data->mutex, NULL);
	forks = malloc(sizeof(pthread_mutex_t) * data->nbr_of_philos);
	disponibility = malloc(sizeof(int) * data->nbr_of_philos);
	index = 0;
	while (index < data->nbr_of_philos)
	{
		pthread_mutex_init(&forks[index], NULL);
		disponibility[index++] = FREE;
	}
	pthread_mutex_init(&data->modif, NULL);
	return (data->death = 0, data->done_dinners = 0, data->count = 0, \
			data->forks = disponibility, data->forchetta = forks, data);
}
