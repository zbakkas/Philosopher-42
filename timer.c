/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakkas <zouhirbakkas@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:19:51 by zbakkas           #+#    #+#             */
/*   Updated: 2024/06/04 17:35:07 by zbakkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	timer(t_args *args)
{
	long	res;

	res = get_current_time() - args->start;
	return (res);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(int milliseconds, t_philo *philo)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
	{
		usleep(200);
		pthread_mutex_lock(&philo->args->m_die);
		if (philo->args->die_s)
		{
			pthread_mutex_unlock(&philo->args->m_die);
			return (0);
		}
		pthread_mutex_unlock(&philo->args->m_die);
	}
	return (0);
}
