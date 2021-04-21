/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc_and_print_sprite.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 11:29:50 by brice             #+#    #+#             */
/*   Updated: 2021/04/21 11:44:34 by brice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_reycasting.h"

void	ft_print_sprite(t_game *img, int draw_end_x, double transform_y,
						const double *z_buffer) //edit
{
	while (img->sprite.stripe < draw_end_x)
	{
		int				texX;
		int				y;
		int				d;
		int				texY;
		unsigned int	color_2;

		texX = (int)(256 * (img->sprite.stripe - (-img->sprite.sprite_width
						/ 2 + img->sprite.sprite_screen_x)) * img->sprite.width
				/ img->sprite.sprite_width) / 256;
		if (transform_y > 0 && img->sprite.stripe > 0 && img->sprite.stripe
			< img->img.width && transform_y < z_buffer[img->sprite.stripe])
		{
			y = img->sprite.draw_start_y;
			while (y < img->sprite.draw_end_y)
			{
				d = (y) * 256 - img->img.height * 128
					+ img->sprite.sprite_height * 128;
				texY = ((d * texHeight) / img->sprite.sprite_height) / 256;
				color_2 = *(unsigned int *)(img->sprite.addr
						+ (texY * img->sprite.line_length + texX
							* (img->sprite.bits_per_pixel / 8)));
				if ((color_2 & 0x00FFFFFF) != 0)
					my_mlx_pixel_put(&img->img, img->sprite.stripe,
						y, (int)color_2);
				y++;
			}
		}
		img->sprite.stripe++;
	}
}

void	ft_calculate_fs(t_game *img, t_sprite *sprite,
						const int *sprite_order, const int *i)
{
	img->sprite.sprite_x = sprite[sprite_order[*i]].x - img->rc.pos_x;
	img->sprite.sprite_y = sprite[sprite_order[*i]].y - img->rc.pos_y;
	img->sprite.inv_det = 1.0 / (img->pos.plane_x * img->vector.v_y
			- img->vector.v_x * img->pos.plane_y);
	img->sprite.transform_x = img->sprite.inv_det * (img->vector.v_y
			* img->sprite.sprite_x - img->vector.v_x * img->sprite.sprite_y);
	img->sprite.transform_y = img->sprite.inv_det * (-img->pos.plane_y
			* img->sprite.sprite_x + img->pos.plane_x * img->sprite.sprite_y);
	img->sprite.sprite_screen_x = (int)(((double)img->img.width / 2)
			* (1 + img->sprite.transform_x / img->sprite.transform_y));
}
