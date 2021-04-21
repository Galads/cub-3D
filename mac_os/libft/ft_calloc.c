/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 06:10:55 by brice             #+#    #+#             */
/*   Updated: 2020/11/11 07:14:48 by brice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*new;
	size_t			i;

	i = 0;
	new = (unsigned char *)malloc(count * size);
	if (new == NULL)
		return (NULL);
	while (i < count * size)
		new[i++] = 0;
	return ((void *)new);
}
