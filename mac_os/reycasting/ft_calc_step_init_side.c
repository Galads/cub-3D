/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc_step_init_side.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 18:39:34 by brice             #+#    #+#             */
/*   Updated: 2021/04/16 18:44:05 by brice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_reycasting.h"

void	ft_calc_step_init_side(t_game *img)
{
	if (img->rc.ray_dir_x < 0)
	{
		img->rc.step_x = -1;
		img->rc.side_dist_x = (img->rc.pos_x - img->rc.map_x)
			* img->rc.delta_dist_x;
	}
	else
	{
		img->rc.step_x = 1;
		img->rc.side_dist_x = (-img->rc.pos_x + 1.0 + img->rc.map_x)
			* img->rc.delta_dist_x;
	}
	if (img->rc.ray_dir_y < 0)
	{
		img->rc.step_y = -1;
		img->rc.side_dist_y = (img->rc.pos_y - img->rc.map_y)
			* img->rc.delta_dist_y;
	}
	else
	{
		img->rc.step_y = 1;
		img->rc.side_dist_y = (-img->rc.pos_y + 1.0 + img->rc.map_y)
			* img->rc.delta_dist_y;
	}
}
