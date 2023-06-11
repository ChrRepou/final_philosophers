/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crepou <crepou@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:41:12 by crepou            #+#    #+#             */
/*   Updated: 2023/06/10 00:59:47 by crepou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static long long	ft_calc_num(const char *end, long len)
{
	long long			num;
	long long			mult;

	mult = 1;
	num = 0;
	end--;
	while (len > 0)
	{
		if (*end == '-')
			num *= -1;
		if (ft_isdigit(*end))
		{
			num += mult * (*end - 48);
			mult *= 10;
		}
		len--;
		end--;
	}
	return (num);
}

static int	ft_allowed_charstr(char c)
{
	if (c == '\n' || c == '\t' || c == '\f')
		return (1);
	if (c == '\v' || c == '\r' || c == 32)
		return (1);
	return (0);
}

long long	ft_atol(const char *str)
{
	long long			len;
	long long			count;

	len = 0;
	count = 0;
	if (ft_strncmp(str, "\0", 1) == 0)
		return (0);
	while (*str != '\0')
	{
		if (*str == '-' || *str == '+' || ft_isdigit(*str))
			break ;
		if (!(ft_allowed_charstr(*str)))
			return (0);
		count++;
		str++;
	}
	str++;
	len++;
	while (ft_isdigit(*str) && *str != '\0')
	{
		len++;
		str++;
	}
	return (ft_calc_num(str, len));
}
