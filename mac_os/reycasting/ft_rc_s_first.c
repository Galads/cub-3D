/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rc_s_first.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 18:03:40 by brice             #+#    #+#             */
/*   Updated: 2021/04/16 18:06:27 by brice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_reycasting.h"

void	ft_rc_s_first(t_game *img, double *z_buffer)
{
	img->rc.pos_x = img->pos.pos_x;
	img->rc.pos_y = img->pos.pos_y;
	img->rc.x = 0;
	while (img->rc.x < img->img.width)
	{
		ft_base_rc_value(img);
		ft_calc_step_init_side(img);
		ft_rc_hit(img);
		if (img->rc.draw_start < 0)
			img->rc.draw_start = 0;
		img->rc.draw_end = img->rc.line_height / 2 + img->img.height / 2;
		if (img->rc.draw_end >= img->img.height)
			img->rc.draw_end = img->img.height - 1;
		if (img->rc.side == 1)
			img->rc.color /= 3;
		if (img->rc.x % 2)
			ft_vertical_line(img, 0,
				img->rc.draw_start, img->rc.col_c);
		ft_print_texture(img);
		z_buffer[img->rc.x] = img->rc.perp_wall_dist;
		ft_vertical_line(img, img->rc.draw_end + 1,
			img->img.height, img->rc.col_f);
		img->rc.x++;
	}
}
