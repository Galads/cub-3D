/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 18:18:06 by brice             #+#    #+#             */
/*   Updated: 2020/11/11 07:30:34 by brice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_cond(char const *s, char const *set)
{
	int i;

	i = 0;
	while (set[i])
	{
		if (*s == set[i])
			return (1);
		i++;
	}
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	if (!s1)
		return (NULL);
	j = ft_strlen(s1);
	while (s1[i] != '\0' && ft_cond(&s1[i], set))
		i++;
	while (s1[j - 1] != '\0' && ft_cond(&s1[j - 1], set))
		j--;
	if (!(str = ft_substr(s1, i, (j - i))))
		return (NULL);
	return (str);
}
