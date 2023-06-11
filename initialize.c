/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crepou <crepou@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:25:30 by crepou            #+#    #+#             */
/*   Updated: 2023/05/23 16:25:30 by crepou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_mutex(t_info *info)
{
	int	philos;
	int	i;

	philos = info->number_of_philos;
	info->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * philos);
	i = -1;
	while (++i < philos)
	{
		if (pthread_mutex_init(&(info->forks[i]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&info->printing, NULL))
		return (1);
	if (pthread_mutex_init(&info->eating, NULL))
		return (1);
	if (pthread_mutex_init(&info->is_dead, NULL))
		return (1);
	if (pthread_mutex_init(&info->satisfied, NULL))
		return (1);
	if (pthread_mutex_init(&info->last_time_eating, NULL))
		return (1);
	return (0);
}

void	initialize_philo(t_philosopher *philo, int i, int number_of_philos)
{
	philo->left_fork = i;
	philo->right_fork = (i + 1) % number_of_philos;
	philo->times_ate = 0;
	philo->id = i;
	philo->is_dead = 0;
	philo->last_time_ate = get_curr_time();
}

int	create_philosophers(t_info *info, t_args *args)
{
	int		philos;
	int		i;

	philos = info->number_of_philos;
	i = -1;
	info->philos = (t_philosopher *)malloc(sizeof(t_philosopher) * philos);
	while (++i < philos)
	{
		args[i].id = i;
		initialize_philo(&info->philos[i], i, info->number_of_philos);
		args[i].info = info;
		args[i].is_dead = 0;
		if (pthread_create(&info->philos[i].philosopher,
				NULL, &actions, &args[i]))
			return (1);
	}
	return (0);
}

int	fill_info(int argc, char *argv[], t_info *info, t_args *args)
{
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	info->number_of_philos = ft_atoi(argv[1]);
	info->init_time = time_diff(0);
	info->all_satisfied = 0;
	info->philo_is_dead = 0;
	if (argc == 6 && ft_atoi(argv[5]) <= 0)
		return (1);
	else if (argc == 6)
		info->number_of_meals = ft_atoi(argv[5]);
	else
		info->number_of_meals = 0;
	if (info->time_to_die < 0 || info->time_to_eat < 0
		|| info->time_to_sleep < 0 || info->number_of_philos < 1)
		return (1);
	if (info->number_of_philos > 200)
		return (printf("do not test with more than 200 philos\n"), 1);
	if (create_mutex(info) || create_philosophers(info, args))
		return (1);
	return (0);
}
