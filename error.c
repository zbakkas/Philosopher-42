/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakkas <zouhirbakkas@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:07:33 by zbakkas           #+#    #+#             */
/*   Updated: 2024/06/06 14:33:50 by zbakkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_n_arguments(int arc)
{
	if (arc != 5 && arc != 6)
	{
		printf("bad arguments\n");
		return (1);
	}
	return (0);
}

int	check_v_arguments(t_args args, int arc)
{
	if (args.t_eat <= 0 || args.t_die <= 0 || args.t_sleep <= 0 
		|| args.philosophers <= 0)
	{
		printf("bad value\n");
		return (1);
	}
	if (arc == 6 && args.w <= 0)
	{
		printf("bad value\n");
		return (1);
	}
	return (0);
}
