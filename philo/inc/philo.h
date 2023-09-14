/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 18:19:24 by cprojean          #+#    #+#             */
/*   Updated: 2023/09/14 23:45:21 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

enum e_status {
	FREE,
	USED
};

enum e_life {
	ALIVE,
	DEAD
};

typedef struct s_data {
	int				count;
	int				death;
	int				sleep_time;
	int				eat_time;
	int				death_timer;
	int				done_dinners;
	int				nbr_of_dinner;
	int				count_philos;
	int				nbr_of_philos;
	int				*forks;
	pthread_mutex_t	modif;
	pthread_mutex_t	mutex;
	pthread_mutex_t	*forchetta;
}	t_data;

typedef struct s_philo {
	t_data			*data;
	pthread_t		tid;
	int				done;
	int				num;
	int				alive;
	int				nbr_of_meals;
	long			last_meal;
	long			creation_time;
	pthread_mutex_t	mutex;
}	t_philo;

//ft_atoi.c
int		ft_atoi(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);

//routine.c
void	handle_philos(t_philo *philo);

//think.c
int		freud(t_philo *philo, int num);

//dinner.c
int		devourer(t_philo *philo, int num);

//rest.c
int		ft_sleep(t_philo *philo);
int		ft_usleep(t_philo *philo, int rest);

//death.c
int		is_anyone_dead(t_philo *philo);
int		do_i_have_time(t_philo *philo, int time);
void	kill_philo(t_philo *philo);

//print_timestamp.c
int		print_timestamp(t_philo *philo, char *str);
long	ft_get_time(void);

//philo.c
void	do_philosophers(t_data *data);
void	free_everything(t_data *data);
t_philo	*initiate_philos(t_data *data, pthread_mutex_t mutex);
t_data	*handle_parameters(int count, char **values);

#endif