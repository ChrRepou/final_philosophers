/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crepou <crepou@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 16:56:59 by crepou            #+#    #+#             */
/*   Updated: 2023/06/10 14:00:06 by crepou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_a_number(char *str)
{
	if (ft_atol(str) < 0)
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	is_an_integer(char *str)
{
	long long int	num;

	num = ft_atol(str);
	if (num > MAX_INT || num < 0)
		return (0);
	return (1);
}

int	error_check(char *str)
{
	if (is_a_number(str) && is_an_integer(str))
	{
		return (0);
	}
	return (1);
}

int	wrong_arg(int j, char **args, char *argv[])
{
	if (args != NULL)
	{
		if (error_check(args[j]))
			return (1);
	}
	else
	{
		if (error_check(argv[j + 1]))
			return (1);
	}
	return (0);
}
