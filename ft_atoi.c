/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crepou <crepou@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:27:40 by crepou            #+#    #+#             */
/*   Updated: 2023/05/24 18:50:30 by crepou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isdigit(int argument)
{
	return ((argument >= 48 && argument <= 57));
}

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	if (*str1 == '\0' && *str2 == '\0')
		n = 0;
	while (n > 0)
	{
		if ((unsigned char)*str1 > (unsigned char)*str2)
			return (1);
		if ((unsigned char)*str2 > (unsigned char)*str1)
			return (-1);
		str1++;
		str2++;
		if (*str1 == '\0' && *str2 == '\0')
			break ;
		n--;
	}
	return (0);
}

static int	ft_calc_num(const char *end, int len)
{
	int			num;
	int			mult;

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

int	ft_atoi(const char *str)
{
	int			len;
	int			count;

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
