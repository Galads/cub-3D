/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 03:42:13 by brice             #+#    #+#             */
/*   Updated: 2021/04/23 10:08:57 by brice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_support_atoi(unsigned long long *res, int *sign)
{
	if (*res > 9223372036854775807)
	{
		if (*sign > 0)
			*res = -1;
		else
			*res = 0;
	}
}

int	ft_atoi(const char *str)
{
	int					i;
	unsigned long long	res;
	int					sign;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == ' ' || str[i] == '\r' || str[i] == '\t'
		|| str[i] == '\f' || str[i] == '\v' || str[i] == '\n')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	ft_support_atoi(&res, &sign);
	return (res * sign);
}
