/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handler_f_c.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 18:27:19 by brice             #+#    #+#             */
/*   Updated: 2021/04/25 18:28:17 by brice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_check_colors(char **result)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (result[i])
	{
		while (result[i][j])
		{
			if (result[(i)][(j)] == ' ' || result[(i)][(j)] == 'F'
				|| result[(i)][j] == 'C')
				(j)++;
			else if (!ft_isdigit(result[(i)][(j)])
					 && result[(i)][(j)] != '\0' && result[(i)][(j)] != ' ' )
			{
				printf("Error: not a valid strings\n");
				exit(13);
			}
			else
				while (ft_isdigit(result[(i)][(j)]))
					(j)++;
		}
		j = 0;
		i++;
	}
}

void	ft_parse_head_if_int_1(char **result, t_game *img)
{
	if (ft_check_addr_mem(result[0], 'F'))
	{
		ft_handler_f_c(&img->rc.col_f, result, img);
		img->j_ps++;
	}
	else if (ft_check_addr_mem(result[0], 'C'))
	{
		ft_handler_f_c(&img->rc.col_c, result, img);
		img->j_ps++;
	}
}

void	ft_handler_f_c(int *col, char **result, t_game *img)
{
	int	rgb[3];

	img->rgb.i = 0;
	img->rgb.j = 1;
	img->rgb.k = 0;
	ft_check_colors(result);
	while (result[img->rgb.i])
	{
		while (result[img->rgb.i][img->rgb.j])
		{
			if (ft_handler_f_c1(result, img, (int *) &rgb) == 1)
				break ;
		}
		img->rgb.j = 0;
		img->rgb.i++;
	}
	*col = ft_create_trgb(0, rgb[0], rgb[1], rgb[2]);
}
