/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crepou <crepou@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:37:12 by crepou            #+#    #+#             */
/*   Updated: 2023/05/26 22:10:45 by crepou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	destroy_mutexes(t_info *info)
{
	int	i;
	int	philos;

	i = -1;
	philos = info->number_of_philos;
	while (++i < philos)
	{
		if (pthread_mutex_destroy(&info->forks[i]))
			return (1);
	}
	if (pthread_mutex_destroy(&info->printing))
		return (1);
	if (pthread_mutex_destroy(&info->eating))
		return (1);
	if (pthread_mutex_destroy(&info->is_dead))
		return (1);
	if (pthread_mutex_destroy(&info->satisfied))
		return (1);
	if (pthread_mutex_destroy(&info->last_time_eating))
		return (1);
	return (0);
}
