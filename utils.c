/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvahib <hvahib@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:18:18 by hvahib            #+#    #+#             */
/*   Updated: 2025/04/23 14:34:32 by hvahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}

int	ft_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_usleep(time_t ms)
{
	time_t	start;
	time_t	end;
	time_t	remaining;

	start = current_time();
	if (start == -1)
		return (1);
	end = start + ms;
	while (1)
	{
		remaining = end - current_time();
		if (remaining <= 0)
			break ;
		if (remaining > 20)
			remaining = 20000;
		else
			remaining *= 1000;
		if (usleep(remaining) == -1)
			return (1);
	}
	return (0);
}

time_t	current_time(void)
{
	struct timeval	now;
	time_t			time_ms;

	if (gettimeofday(&now, NULL) == -1)
	{
		ft_putendl_fd("Error: Gettimeofday failed", 2);
		return (-1);
	}
	time_ms = now.tv_sec * 1000 + now.tv_usec / 1000;
	return (time_ms);
}
