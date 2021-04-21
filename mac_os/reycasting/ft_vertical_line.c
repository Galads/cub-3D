/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vertical_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 18:47:24 by brice             #+#    #+#             */
/*   Updated: 2021/04/21 12:18:32 by brice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_reycasting.h"

void	ft_vertical_line(t_data *img, int x, int draw_start,
		int draw_end, int color)
{
	int	i;

	i = draw_start;
	while (i < draw_end)
	{
		my_mlx_pixel_put(img, x, i, color);
		i++;
	}
}
