/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crepou <crepou@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:44:42 by crepou            #+#    #+#             */
/*   Updated: 2023/05/23 16:44:42 by crepou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_all(t_info *info, t_args *args)
{
	destroy_mutexes(info);
	free(info->forks);
	free(info->philos);
	free(info);
	free(args);
}

int	init_phil(t_info	*info, t_args *args)
{
	if (info->number_of_philos == 1)
	{
		action_print(info, &info->philos[0],
			"has taken a fork", time_diff(info->init_time));
		usleep(info->time_to_die * 1000);
		action_print(info, &info->philos[0],
			"is dead", time_diff(info->init_time));
		destroy_threads(info);
		free_all(info, args);
		return (-1);
	}
	return (0);
}

//int	free_after_death(t_info *info, int died)
//{
//	if (died)
//	{
//		destroy_threads(info);
//		destroy_mutexes(info);
//		free(info->forks);
//		free(info->philos);
//		free(info);
//		return (-1);
//	}
//	return (0);
//}

int	philosophers(char *argv[], int argc)
{
	t_info	*info;
	t_args	*args;

	info = (t_info *)malloc(sizeof(t_info));
	if (!info)
		return (-1);
	args = (t_args *)malloc(sizeof(t_args) * ft_atoi(argv[1]));
	if (fill_info(argc, argv, info, args))
	{
		free(info);
		free(args);
		return (-1);
	}
	if (init_phil(info, args) == -1)
		return (-1);
	check_if_dead(info);
	if (join_threads(info))
		return (-1);
	free_all(info, args);
	return (0);
}
