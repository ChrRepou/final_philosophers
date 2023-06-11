/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crepou <crepou@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:12:18 by crepou            #+#    #+#             */
/*   Updated: 2023/06/10 01:04:32 by crepou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	get_curr_time(void)
{
	long long		time_in_mill;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time_in_mill = (tv.tv_sec) * 1000LL + (tv.tv_usec) / 1000 ;
	return (time_in_mill);
}

long long	time_diff(long long previous)
{
	long long	curr_time;

	curr_time = get_curr_time();
	return (curr_time - previous);
}

int	ft_isprint(int argument)
{
	return ((argument >= 32) && (argument <= 126));
}
