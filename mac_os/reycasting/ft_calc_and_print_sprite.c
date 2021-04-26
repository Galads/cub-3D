/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc_and_print_sprite.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 11:29:50 by brice             #+#    #+#             */
/*   Updated: 2021/04/25 17:56:28 by brice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_reycasting.h"

static void	ft_print_sprite_while(t_game *img, int *tex_x, int *tex_y)
{
	while (img->y_s < img->sprite.draw_end_y)
	{
		img->d_s = (img->y_s) * 256 - img->img.height * 128
			+ img->sprite.sprite_height * 128;
		(*tex_y) = ((img->d_s * img->texture_n.width)
				/ img->sprite.sprite_height) / 256;
		img->color_2 = *(unsigned int *)(img->sprite.addr
				+ ((*tex_y) * img->sprite.line_length + (*tex_x)
					* (img->sprite.bits_per_pixel / 8)));
		if ((img->color_2 & 0x00FFFFFF) != 0)
			my_mlx_pixel_put(&img->img, img->sprite.stripe,
				img->y_s, (int)img->color_2);
		img->y_s++;
	}
}

void	ft_print_sprite(t_game *img, int draw_end_x, double transform_y,
					 const double *z_buffer)
{
	int	tex_x;
	int	tex_y;

	img->y_s = 0;
	img->d_s = 0;
	img->color_2 = 0;
	while (img->sprite.stripe < draw_end_x)
	{
		tex_x = (int)(256 * (img->sprite.stripe - (-img->sprite.sprite_width
						/ 2 + img->sprite.sprite_screen_x)) * img->sprite.width
				/ img->sprite.sprite_width) / 256;
		if (transform_y > 0 && img->sprite.stripe
			< img->img.width && transform_y < z_buffer[img->sprite.stripe])
		{
			img->y_s = img->sprite.draw_start_y;
			ft_print_sprite_while(img, &tex_x, &tex_y);
		}
		img->sprite.stripe++;
	}
}

void	ft_calculate_fs(t_game *img, t_sprite *sprite,
					 const int *sprite_order, int *i)
{
	img->sprite.sprite_x = sprite[sprite_order[(*i)]].x - img->rc.pos_x;
	img->sprite.sprite_y = sprite[sprite_order[(*i)]].y - img->rc.pos_y;
	img->sprite.inv_det = 1.0 / (img->pos.plane_x * img->vector.v_y
			- img->vector.v_x * img->pos.plane_y);
	img->sprite.transform_x = img->sprite.inv_det * (img->vector.v_y
			* img->sprite.sprite_x - img->vector.v_x * img->sprite.sprite_y);
	img->sprite.transform_y = img->sprite.inv_det * (-img->pos.plane_y
			* img->sprite.sprite_x + img->pos.plane_x * img->sprite.sprite_y);
	img->sprite.sprite_screen_x = (int)(((double)img->img.width / 2)
			* (1 + img->sprite.transform_x / img->sprite.transform_y));
}
