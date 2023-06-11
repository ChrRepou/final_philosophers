/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crepou <crepou@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 17:21:21 by crepou            #+#    #+#             */
/*   Updated: 2023/06/11 17:03:23 by crepou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	satisfaction_check(t_info *info)
{
	pthread_mutex_lock(&info->is_dead);
	if (info->philo_is_dead)
	{
		pthread_mutex_unlock(&info->is_dead);
		return (1);
	}
	pthread_mutex_unlock(&info->is_dead);
	pthread_mutex_lock(&info->satisfied);
	if (info->all_satisfied)
	{
		pthread_mutex_unlock(&info->satisfied);
		return (1);
	}
	pthread_mutex_unlock(&info->satisfied);
	return (0);
}

int	count_meals(t_info *info)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&info->eating);
	while (info->number_of_meals != 0 && i < info->number_of_philos
		&& info->philos[i].times_ate >= info->number_of_meals)
		i++;
	pthread_mutex_unlock(&info->eating);
	return (i);
}

int	ft_kill(t_info *info, long long last, int i)
{
	int	is_dead;

	pthread_mutex_lock(&info->is_dead);
	is_dead = info->philo_is_dead;
	pthread_mutex_unlock(&info->is_dead);
	if (is_dead)
		return (1);
	if (time_diff(info->init_time) - last > (long long int)info->time_to_die)
	{
		action_print(info, &info->philos[i], "is dead",
			time_diff(info->init_time));
		pthread_mutex_lock(&info->is_dead);
		info->philo_is_dead = 1;
		pthread_mutex_unlock(&info->is_dead);
		return (1);
	}
	return (0);
}

int	eating_proc(t_info *info, t_philosopher *philosopher)
{
	pthread_mutex_lock(&info->is_dead);
	if (info->philo_is_dead)
	{
		pthread_mutex_unlock(&info->is_dead);
		return (1);
	}
	pthread_mutex_unlock(&info->is_dead);
	action_print(info, philosopher, "has taken a fork",
		time_diff(info->init_time));
	pthread_mutex_lock(&info->eating);
	action_print(info, philosopher, "is eating", time_diff(info->init_time));
	philosopher->last_time_ate = time_diff(info->init_time);
	philosopher->times_ate++;
	pthread_mutex_unlock(&info->eating);
	usleep(1000 * info->time_to_eat);
	return (0);
}
