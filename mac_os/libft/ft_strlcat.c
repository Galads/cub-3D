/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 12:33:08 by brice             #+#    #+#             */
/*   Updated: 2020/11/11 08:00:44 by brice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	k;
	size_t	l;

	i = 0;
	k = 0;
	l = 0;
	while (dst[i] != '\0' && i < dstsize)
		i++;
	if (dstsize <= i)
		return (ft_strlen(src) + dstsize);
	l = i;
	i = ft_strlen(dst);
	while ((i + k + 1) < dstsize && src[k])
	{
		dst[l] = src[k];
		l++;
		k++;
	}
	dst[l] = '\0';
	return (i + ft_strlen(src));
}
