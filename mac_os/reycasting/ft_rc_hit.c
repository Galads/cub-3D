/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rc_hit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 18:13:46 by brice             #+#    #+#             */
/*   Updated: 2021/04/16 18:23:14 by brice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_reycasting.h"

void	ft_rc_hit(t_game *img)
{
	while (img->rc.hit == 0)
	{
		if (img->rc.side_dist_x < img->rc.side_dist_y)
		{
			img->rc.side_dist_x += img->rc.delta_dist_x;
			img->rc.map_x += img->rc.step_x;
			img->rc.side = 0;
		}
		else
		{
			img->rc.side_dist_y += img->rc.delta_dist_y;
			img->rc.map_y += img->rc.step_y;
			img->rc.side = 1;
		}
		if (img->world_map[img->rc.map_x][img->rc.map_y] == '1')
			img->rc.hit = 1;
	}
	if (img->rc.side == 0)
		img->rc.perp_wall_dist = (img->rc.map_x - img->rc.pos_x + (double)
				(1 - img->rc.step_x) / 2) / img->rc.ray_dir_x;
	else
		img->rc.perp_wall_dist = (img->rc.map_y - img->rc.pos_y + (double)
				(1 - img->rc.step_y) / 2) / img->rc.ray_dir_y;
	img->rc.line_height = (int)(img->img.height / img->rc.perp_wall_dist);
	img->rc.draw_start = img->img.height / 2 - img->rc.line_height / 2;
}
