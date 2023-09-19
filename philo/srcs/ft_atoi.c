/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:07:22 by cprojean          #+#    #+#             */
/*   Updated: 2023/09/19 12:50:33 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_filler(long answer, const char *str, int sign, int index)
{
	while (('0' <= str[index] && str[index] <= '9'))
	{
		if (answer != ((answer * 10) + (str[index] - '0')) / 10 && sign == -1)
			return (0);
		if (answer != ((answer * 10) + (str[index] - '0')) / 10 && sign == 1)
			return (-1);
		answer = answer * 10 + str[index] - 48;
		index++;
	}
	return (sign * answer);
}

int	ft_atoi(const char *str)
{
	int		index;
	int		sign;
	long	answer;

	answer = 0;
	sign = 1;
	index = 0;
	while ((9 <= str[index] && str[index] <= 13) || (str[index] == ' '))
		index++;
	if (str[index] == '-')
	{
		sign = -1;
		index++;
	}
	else if (str[index] == '+')
		index++;
	return (ft_filler(answer, str, sign, index));
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (ft_strlen(s1) == 0 || ft_strlen(s2) == 0)
		return (1);
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && i < n && s1[i] != '\0' && s2[i] != '\0')
		i++;
	if (i == n)
		i--;
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}
