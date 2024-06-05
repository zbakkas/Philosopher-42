/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakkas <zouhirbakkas@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:36:03 by zbakkas           #+#    #+#             */
/*   Updated: 2024/06/05 10:59:18 by zbakkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
// typedef struct s_args t_args;

typedef struct s_philo
{
	int				n_philo;
	pthread_t		thread;
	struct s_args	*args;
	pthread_mutex_t	m_l_fork;
	pthread_mutex_t	*m_r_fork;
	int				c_eat;
	size_t			last_eat;
}t_philo;

typedef struct s_args
{
	int				philosophers;
	int				forks; 
	int				t_die;
	int				die_s;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
	int				w;
	int				finish;
	size_t			start;
	long int		time;
	pthread_mutex_t	m_die;
	pthread_mutex_t	m_write;
	pthread_mutex_t	m_eat;
	t_philo			*philo;
}t_args;

int			ft_atoi(char *str);
size_t		timer(t_args *args);
int			ft_usleep(size_t milliseconds, t_philo *philo);
size_t		get_current_time(void);
void		check(t_args *args);
void		initialize_data(t_args *args, int arc, char **arv);

void		message(char *str, t_philo *philo);
void		take_forks(t_philo *philo);
void		dow_forks(t_philo *philo);
void		eat(t_philo *philo);

int			ft_strcmp(char *s1, char *s2);

#endif