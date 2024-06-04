/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakkas <zouhirbakkas@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:23:05 by zbakkas           #+#    #+#             */
/*   Updated: 2024/06/04 17:30:44 by zbakkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

void	message(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->args->m_write);
	if (!philo->args->die_s && strcmp("died", str) == 0)
	{
		printf("%ld %d %s\n", timer(philo->args), philo->n_philo, str);
		pthread_mutex_lock(&philo->args->m_die);
		philo->args->die_s = 1;
		pthread_mutex_unlock(&philo->args->m_die);
	}
	if (!philo->args->die_s)
		printf("%ld %d %s\n", timer(philo->args), philo->n_philo, str);
	pthread_mutex_unlock(&philo->args->m_write);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->m_r_fork);
	message("has taken a fork", philo);
	pthread_mutex_lock(&philo->m_l_fork);
	message("has taken a fork", philo);
}

void	dow_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->m_r_fork);
	pthread_mutex_unlock(&philo->m_l_fork);
	message("is sleeping", philo);
	ft_usleep(philo->args->t_sleep, philo);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	message(" is eating", philo);
	pthread_mutex_lock(&philo->args->m_eat);
	philo->last_eat = timer(philo->args);
	philo->c_eat += 1;
	pthread_mutex_unlock(&philo->args->m_eat);
	ft_usleep(philo->args->t_eat, philo);
	dow_forks(philo);
}

int	main(int arc, char **arv)
{
	t_args	args;
	int		i;

	i = 0;
	initialize_data(&args, arc, arv);
	check(&args);
	i = 0;
	while (i < args.philosophers)
	{
		pthread_join(args.philo[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < args.philosophers)
	{
		pthread_mutex_destroy(&args.philo[i].m_l_fork);
		// pthread_mutex_destroy(&args.philo[i].m_l_fork);
		i++;
	}
	free(args.philo);
	pthread_mutex_destroy(&args.m_die);
	pthread_mutex_destroy(&args.m_eat);
}
