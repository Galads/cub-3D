/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 00:02:14 by brice             #+#    #+#             */
/*   Updated: 2020/11/11 07:56:39 by brice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_size(long long int new)
{
	int	sign;
	int	sum;

	sum = 0;
	if (new >= 0)
		sign = 1;
	else
		sign = -1;
	while (new / 10)
	{
		new /= 10;
		sum++;
	}
	sum++;
	return (sum * sign);
}

static	char	*ft_while(char *str, int sum, long long int new, int sign)
{
	while (sum > 0)
	{
		if (sign < 0)
		{
			str[0] = '-';
			str[sum--] = new % 10 + '0';
			new /= 10;
			continue;
		}
		str[sum-- - 1] = new % 10 + '0';
		new /= 10;
	}
	return (str);
}

char			*ft_itoa(int n)
{
	char			*str;
	int				sum;
	long long int	new;
	int				sign;

	sign = 1;
	new = n;
	sum = ft_size(new);
	if (sum > 0)
		str = ft_calloc(sizeof(char), sum + 1);
	else
	{
		str = ft_calloc(sizeof(char), (sum * -1) + 2);
		sign = -1;
		sum *= -1;
		new *= -1;
	}
	if (!str)
		return (NULL);
	str = ft_while(str, sum, new, sign);
	return (str);
}
