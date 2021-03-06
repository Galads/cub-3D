/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_inter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 17:22:13 by brice             #+#    #+#             */
/*   Updated: 2021/04/25 17:26:04 by brice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_parse_head_wh_l(t_game *img, char **result)
{
	int	i;

	i = 0;
	while (result[i] && i < 1)
	{
		ft_parse_t_a_s((const char **) result, img);
		ft_parse_str((const char **) result, img);
		ft_fill_flag(img);
		img->flag_parser = 0;
		i++;
	}
}

void	ft_parse_head(char **line, t_game *img)
{
	char	**result;
	int		i;
	int		a;

	i = 0;
	result = ft_split(*line, ' ');
	if (*result)
	{
		if (!ft_strncmp(result[0], "F", INT_MAX)
			|| !ft_strncmp(result[0], "C", INT_MAX))
		{
			while (result[i])
				i++;
			a = ft_check_str_num(line);
			if (a < 0 || a == 0)
				return ;
			if (!ft_parse_head_if_int(img, result, line, &i))
				return ;
		}
	}
	ft_parse_head_wh_l(img, result);
	ft_free_split(result);
}
