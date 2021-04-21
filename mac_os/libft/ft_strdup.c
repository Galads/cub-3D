/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 06:42:24 by brice             #+#    #+#             */
/*   Updated: 2020/11/05 07:24:21 by brice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = ft_strlen(s1);
	new = (char *)malloc(sizeof(char) * j + 1);
	if (new == NULL)
		return (NULL);
	while (i < j)
	{
		*(new + i) = *(s1 + i);
		i++;
	}
	*(new + i) = '\0';
	return (new);
}
