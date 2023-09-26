/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 19:36:05 by cprojean          #+#    #+#             */
/*   Updated: 2023/09/26 12:36:50 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void		join_philo(t_data *data, t_philo **philo);
static t_philo	*initiate_philos(t_data *data, pthread_mutex_t mutex);

void	do_philosophers(t_data *data)
{
	int				i;
	pthread_mutex_t	mutex;
	t_philo			*philo;

	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	i = 0;
	philo = initiate_philos(data, mutex);
	pthread_mutex_lock(&mutex);
	while (i < data->nbr_of_philos)
	{
		if (pthread_create(&philo[i].tid, NULL, \
			(void *)handle_philos, &philo[i]) != 0)
		{
			pthread_mutex_unlock(&mutex);
			return ;
		}
		else
			i++;
	}
	pthread_mutex_unlock(&mutex);
	join_philo(data, &philo);
	free(philo);
}

static void	join_philo(t_data *data, t_philo **philo)
{
	int	i;

	i = 0;
	while (i < data->nbr_of_philos)
	{
		pthread_join(philo[i]->tid, NULL);
		i++;
	}
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

static t_philo	*initiate_philos(t_data *data, pthread_mutex_t mutex)
{
	int				index;
	t_philo			*philo;
	long			time;

	index = 0;
	time = ft_get_time();
	philo = malloc(sizeof(t_philo) * data->nbr_of_philos);
	if (!philo)
		return (NULL);
	while (index < data->nbr_of_philos)
	{
		philo[index].data = data;
		philo[index].num = index + 1;
		philo[index].last_meal = 0;
		philo[index].nbr_of_meals = 0;
		philo[index].alive = ALIVE;
		philo[index].mutex = mutex;
		philo[index].creation_time = time;
		index++;
	}
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
	pthread_mutex_init(&data->print, NULL);
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
