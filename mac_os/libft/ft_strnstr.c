/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 23:02:00 by brice             #+#    #+#             */
/*   Updated: 2020/11/06 18:48:23 by brice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char		*haystack_val;
	char		*needle_val;
	size_t		i;
	size_t		j;

	haystack_val = (char *)haystack;
	needle_val = (char *)needle;
	i = ft_strlen(needle_val);
	j = 0;
	if (*needle_val == '\0')
		return (haystack_val);
	while (*haystack_val != '\0')
	{
		if (j + i > len)
			return (0);
		if (!ft_strncmp(haystack_val, needle_val, i))
			return (haystack_val);
		haystack_val++;
		j++;
	}
	return (0);
}
