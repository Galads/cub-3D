/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base_rc_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 18:36:22 by brice             #+#    #+#             */
/*   Updated: 2021/04/16 18:37:07 by brice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_reycasting.h"

void 	ft_base_rc_value(t_game *img)
{
	img->rc.color = RGB_1;
	img->rc.camera_x = 2 * img->rc.x / ((double)img->img.width) - 1;
	img->rc.ray_dir_x = img->vector.v_x + img->pos.plane_x * img->rc.camera_x;
	img->rc.ray_dir_y = img->vector.v_y + img->pos.plane_y * img->rc.camera_x;
	img->rc.delta_dist_x = fabs(1 / img->rc.ray_dir_x);
	img->rc.delta_dist_y = fabs(1 / img->rc.ray_dir_y);
	img->rc.map_x = (int) img->rc.pos_x;
	img->rc.map_y = (int) img->rc.pos_y;
	img->rc.hit = 0;
}
