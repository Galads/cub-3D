/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 17:20:16 by brice             #+#    #+#             */
/*   Updated: 2021/04/25 17:20:18 by brice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_free_split(char **line)
{
	int	i;

	i = 0;
	while (line[i])
		free(line[i++]);
	free(line);
}

int	ft_check_addr_mem(char *result, char c)
{
	int		i;
	char	*r_s;

	r_s = NULL;
	i = 0;
	while (result[i])
	{
		if (result[i] == c)
			r_s = &(result[i]);
		if (result[i] >= '0' && result[i] <= '9' && r_s != NULL)
		{
			if (r_s < (&result[i]))
				return (1);
		}
		i++;
	}
	return (0);
}

int	ft_check_str_num_if(char **result, int *i, int *j, int *k)
{
	if (result[0][*i] >= '0' && result[0][*i] <= '9')
	{
		while (result[0][*i] != ' ' && result[0][*i] != ','
			   && result[0][*i] != '\0')
		{
			if ((*j) > 4)
				return (0);
			(*j)++;
			(*i)++;
		}
		(*k)++;
	}
	return (1);
}

int	ft_check_str_num(char **result)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (i < ft_strlen(result[0]))
	{
		if (!ft_check_str_num_if(result, &i, &j, &k))
			return (0);
		if (result[0][i] == ' ' || result[0][i] == ',')
			j = 0;
		if ((k == 3 && (result[0][i] > 0 && result[0][i] < 32))
				|| (k == 3 && (result[0][i] > 32 && result[0][i] <= 127)))
			k++;
		if (k > 3)
			return (-1);
		i++;
	}
	return (1);
}

int	ft_parse_head_if_int(t_game *img, char **result, char **line, int *i)
{
	if ((((*i) <= 6 && !ft_strncmp(result[0], "F", INT_MAX)) || ((*i) <= 6
				&& !ft_strncmp(result[0], "C", INT_MAX)))
		&& ft_check_str_num(line))
	{
		ft_free_split(result);
		result = ft_split(*line, ',');
		*i = 0;
		while (result[(*i)])
			(*i)++;
		if (*i == 3)
			ft_parse_head_if_int_1(result, img);
		ft_free_split(result);
		return (0);
	}
	return (1);
}
