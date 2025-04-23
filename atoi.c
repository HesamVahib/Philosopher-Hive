/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvahib <hvahib@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:08:05 by hvahib            #+#    #+#             */
/*   Updated: 2025/03/12 15:08:33 by hvahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	big_int(int sign)
{
	if (sign == 1)
		return (2147483647);
	if (sign == -1)
		return (-2147483648);
	return (0);
}

static int	very_big_checker(const char *str, int sign)
{
	size_t	count;
	int		res;

	count = 0;
	res = 1;
	while (str[count] && (str[count] >= '0' && str[count] <= '9'))
	{
		count++;
		if (count > 18 && sign == -1)
		{
			res = 0;
			return (0);
		}
		else if (count > 17 && sign == 1)
		{
			res = -1;
			return (-1);
		}
	}
	return (res);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	int		num;

	i = 0;
	num = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (very_big_checker(&str[i], sign) <= 0)
		return (very_big_checker(&str[i], sign));
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (num > (2147483647 - (str[i] - '0')) / 10)
			return (big_int(sign));
		num = num * 10 + (str[i++] - '0');
	}
	return (num * sign);
}
