/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 19:25:20 by cprojean          #+#    #+#             */
/*   Updated: 2023/09/02 19:31:30 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_args(char **argv, int argc);
static int	is_num(char *str);
static int	ft_isdigit(int c);

int	main(int ac, char **av)
{
	t_data	*data;
	int		count;

	count = ac - 2;
	if (!((count == 3) || (count == 4)))
		return (printf("Wrong number of arguments\n"), 1);
	else
	{
		if (check_args(av, ac) == DEAD)
			return (printf("Error in one of the arguments\n"), 1);
		data = handle_parameters(count, av);
		do_philosophers(data);
		free_everything(data);
	}
	return (0);
}

static int	check_args(char **argv, int argc)
{
	int	i;

	i = 1;
	while (i <= argc)
	{
		if (is_num(argv[i]) == ALIVE)
			i++;
		else
			return (DEAD);
	}
	return (ALIVE);
}

static int	is_num(char *str)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(str))
	{
		if (ft_isdigit(str[i]) == 1)
			i++;
		else
			return (DEAD);
	}
	return (ALIVE);
}

static int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (1);
	else
		return (0);
}
