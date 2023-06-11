/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crepou <crepou@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:32:48 by crepou            #+#    #+#             */
/*   Updated: 2023/05/23 16:32:48 by crepou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	eat(t_info *info, t_philosopher *philosopher)
{
	if (info->number_of_philos < 2)
		return (1);
	pthread_mutex_lock(&info->forks[philosopher->left_fork]);
	pthread_mutex_lock(&info->is_dead);
	if (info->philo_is_dead)
	{
		pthread_mutex_unlock(&info->is_dead);
		pthread_mutex_unlock(&info->forks[philosopher->left_fork]);
		return (1);
	}
	pthread_mutex_unlock(&info->is_dead);
	action_print(info, philosopher, "has taken a fork",
		time_diff(info->init_time));
	pthread_mutex_lock(&info->forks[philosopher->right_fork]);
	if (eating_proc(info, philosopher))
	{
		pthread_mutex_unlock(&info->forks[philosopher->left_fork]);
		pthread_mutex_unlock(&info->forks[philosopher->right_fork]);
		return (1);
	}
	pthread_mutex_unlock(&info->forks[philosopher->left_fork]);
	pthread_mutex_unlock(&info->forks[philosopher->right_fork]);
	return (0);
}

int	check_if_dead(t_info *info)
{
	int	i;

	i = -1;
	while (!info->all_satisfied)
	{
		while (++i < info->number_of_philos && !info->philo_is_dead)
		{
			pthread_mutex_lock(&info->eating);
			if (ft_kill(info, info->philos[i].last_time_ate, i))
				return (1);
			pthread_mutex_unlock(&info->eating);
			usleep(250);
		}
		i = count_meals(info);
		pthread_mutex_lock(&info->satisfied);
		if (i == info->number_of_philos)
			info->all_satisfied = 1;
		pthread_mutex_unlock(&info->satisfied);
	}
	return (0);
}

void	*actions(void *args)
{
	t_info	*info;

	info = (*(t_args *)args).info;
	if ((*(t_args *)args).id % 2)
		usleep(15000);
	while (!info->philo_is_dead)
	{
		if (eat(info, &info->philos[(*(t_args *)args).id]))
			break ;
		if (satisfaction_check(info))
			break ;
		action_print(info, &info->philos[(*(t_args *)args).id],
			"is sleeping", time_diff(info->init_time));
		usleep(1000 * info->time_to_sleep);
		if (info->philo_is_dead)
			break ;
		action_print(info, &info->philos[(*(t_args *)args).id],
			"is thinking", time_diff(info->init_time));
	}
	destroy_mutexes(info);
	return (NULL);
}

void	action_print(t_info *info, t_philosopher *philosopher,
	char *str, long long timestamp)
{
	pthread_mutex_lock(&info->printing);
	printf("%lld philosopher %d %s\n", timestamp, philosopher->id, str);
	pthread_mutex_unlock(&info->printing);
}
