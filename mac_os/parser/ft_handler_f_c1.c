/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handler_f_c1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 18:28:47 by brice             #+#    #+#             */
/*   Updated: 2021/04/25 18:29:04 by brice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int 	ft_handler_f_c1(char **result, t_game *img, int *rgb)
{
	if (result[img->rgb.i][img->rgb.j] == ' '
		|| result[img->rgb.i][img->rgb.j] == 'F'
		|| result[img->rgb.i][img->rgb.j] == 'C')
		(img->rgb.j)++;
	else if (ft_isdigit(result[img->rgb.i][img->rgb.j]))
	{
		rgb[(img->rgb.k)++] = ft_atoi(&result[img->rgb.i][img->rgb.j]);
		return (1);
	}
	else
		exit(1);
	return (2);
}
