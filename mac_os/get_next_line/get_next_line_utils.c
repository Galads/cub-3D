/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 22:37:30 by brice             #+#    #+#             */
/*   Updated: 2021/04/23 12:29:24 by brice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../libft/libft.h"

int	ft_exit_code(int isexit, int res)
{
	if (!isexit && res > 0)
		return (1);
	if (res == -1)
		return (-1);
	else
		return (0);
}

int	fill_remainder(char **current, char **remainder, char **buf, int *isexit)
{
	*current = ft_strchr(*buf, '\n');
	if (*current)
	{
		**current = '\0';
		*remainder = ft_strdup(++(*current));
		if (!*remainder)
		{
			free(*buf);
			return (0);
		}
		*isexit = 0;
	}
	return (1);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char)
			* (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!str)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str[i++] = s2[j];
		j++;
	}
	str[i] = '\0';
	return (str);
}
