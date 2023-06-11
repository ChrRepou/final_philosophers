/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crepou <crepou@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:44:35 by crepou            #+#    #+#             */
/*   Updated: 2023/06/11 21:02:08 by crepou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_get_arguments(char *argv[], int argc, char ***args)
{
	int	i;

	if (argc == 2)
	{
		i = 0;
		(*args) = ft_split(argv[1], ' ');
		while ((*args)[i])
		{
			i++;
		}
		return (i);
	}
	(*args) = NULL;
	return (argc - 1);
}

int	main(int argc, char *argv[])
{	
	int		i;
	char	**args;

	i = 1;
	args = NULL;
	if (argc < 5 || argc > 6)
	{
		printf("Not right amount of args. \nFunction prototype:");
		printf("./philo number_of_philos time_to_die \
			time_to_eat time_to_sleep [number_of_meals]\n");
		return (-1);
	}
	while (i < argc - 1)
	{
		ft_get_arguments(argv, argc, &args);
		if (wrong_arg(i, args, argv))
		{
			printf("wrong arguments\n");
			printf("Function prototype:./philo number_of_philos time_to_die \
				time_to_eat time_to_sleep [number_of_meals]\n");
			return (-1);
		}
		i++;
	}
	return (philosophers(argv, argc));
}
