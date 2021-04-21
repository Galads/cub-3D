/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isaint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 12:29:07 by brice             #+#    #+#             */
/*   Updated: 2021/04/21 12:31:25 by brice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "my_cube.h"

int	ft_isaint(int c)
{
	return (c >= 0 && c <= INT_MAX);
}
