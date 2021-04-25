/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_if_f.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 17:06:02 by brice             #+#    #+#             */
/*   Updated: 2021/04/25 17:06:27 by brice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_check_if_f(t_game *img, char **result)
{
	if (img->flag_parser & S && result[1] && !result[2])
	{
		img->sprite.relative_path = ft_strdup((char *)result[1]);
		img->j_ps++;
	}
	if (img->flag_parser & NO && result[1] && !result[2])
	{
		img->texture_n.relative_path = ft_strdup((char *)result[1]);
		img->j_ps++;
	}
	if (img->flag_parser & SO && result[1] && !result[2])
	{
		img->texture_s.relative_path = ft_strdup((char *)result[1]);
		img->j_ps++;
	}
}
