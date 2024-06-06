/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakkas <zouhirbakkas@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:21:28 by zbakkas           #+#    #+#             */
/*   Updated: 2024/06/06 16:13:25 by zbakkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*one_philo(void *arg)
{
	t_args			*args;

	args = (t_args *) arg;
	printf("0 1 is thinking\n0 1 has taken a fork\n");
	usleep(args->t_die * 1000);
	printf("%d 1 died", args->t_die);
	return (NULL);
}

static void	*routine(void *arg)
{
	t_philo			*args;

	args = (t_philo *) arg;
	if (args->n_philo % 2 == 0)
	{
		message("is sleeping", args);
		ft_usleep(args->args->t_sleep, args);
	}
	while (1)
	{
		pthread_mutex_lock(&args->args->m_die);
		pthread_mutex_lock(&args->args->m_eat);
		if (args->args->die_s || args->args->finish >= args->args->philosophers)
		{
			pthread_mutex_unlock(&args->args->m_eat);
			pthread_mutex_unlock(&args->args->m_die);
			break ;
		}
		pthread_mutex_unlock(&args->args->m_eat);
		pthread_mutex_unlock(&args->args->m_die);
		message("is thinking", args);
		eat(args);
	}
	return (NULL);
}

static void	initialize_philo(t_args *args, int i)
{
	if (args->philosophers == 1)
	{
		pthread_create(&args->philo[i].thread, NULL, one_philo, args);
		return ;
	}
	args->philo[i].args = args;
	args->philo[i].n_philo = i + 1;
	args->philo[i].last_eat = 0;
	args->philo[i].c_eat = 0;
	args->philo[i].m_r_fork = NULL;
	pthread_mutex_init(&args->philo[i].m_l_fork, NULL);
	if (i == args->philosophers - 1)
		args->philo[i].m_r_fork = &args->philo[0].m_l_fork;
	else
		args->philo[i].m_r_fork = &args->philo[i + 1].m_l_fork;
	pthread_create(&args->philo[i].thread, NULL, routine, &args->philo[i]);
}

int	initialize_data(t_args *args, int arc, char **arv)
{
	int	i;

	i = 0;
	args->die_s = 0;
	args->finish = 0;
	args->philosophers = ft_atoi(arv[1]);
	args->forks = args->philosophers;
	args->t_die = ft_atoi(arv[2]);
	args->t_eat = ft_atoi(arv[3]);
	args->t_sleep = ft_atoi(arv[4]);
	if (arc == 6)
		args->w = ft_atoi(arv[5]);
	else
		args->w = -1;
	if (check_v_arguments(*args, arc))
		return (1);
	pthread_mutex_init(&args->m_die, NULL); 
	pthread_mutex_init(&args->m_write, NULL); 
	pthread_mutex_init(&args->m_eat, NULL);
	args->philo = malloc(sizeof(args->philo) * args->philosophers);
	args->start = get_current_time();
	while (i < args->philosophers)
		initialize_philo(args, i++);
	return (0);
}

void	check(t_args *args)
{
	int	i;

	while (1 && args->philosophers != 1)
	{
		i = 0;
		while (i < args->philosophers)
		{
			pthread_mutex_lock(&args->m_eat);
			if (args->philo[i].c_eat == args->w)
			{
				args->philo[i].c_eat = 0;
				args->finish++;
			}
			if (timer(args) - args->philo[i].last_eat 
				>= (unsigned long)args->t_die)
			{
				if (args->finish < args->philosophers)
					message("died", &args->philo[i]);
				pthread_mutex_unlock(&args->m_eat);
				return ;
			}
			i++;
			pthread_mutex_unlock(&args->m_eat);
		}
	}
}
