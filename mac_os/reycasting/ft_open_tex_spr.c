/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_tex_spr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 12:04:35 by brice             #+#    #+#             */
/*   Updated: 2021/04/21 12:06:35 by brice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_reycasting.h"

void	ft_texture(t_data *texture, t_game *img, char *str)
{
	texture->relative_path = str;
	texture->img = mlx_xpm_file_to_image(img->img.mlx,
			texture->relative_path, &texture->width, &texture->height);
	if (texture->img == NULL)
	{
		printf("Texture : %s", texture->relative_path);
		ft_print_error(img, "no find", 1);
	}
	texture->addr = mlx_get_data_addr(texture->img,
			&texture->bits_per_pixel, &texture->line_length, &texture->endian);
	if (*texture->addr == '\0')
	{
		printf ("Error: no find addr %s\n", texture->addr);
		ft_print_error(img, "", 1);
	}
}

void	ft_sprite(t_sprite *sprite, t_game *img, char *str)
{
	sprite->relative_path = str;
	sprite->img = mlx_xpm_file_to_image(img->img.mlx,
			sprite->relative_path, &sprite->width, &sprite->height);
	if (sprite->img == NULL)
		ft_print_error(img, sprite->relative_path, 1);
	sprite->addr = mlx_get_data_addr(sprite->img,
			&sprite->bits_per_pixel, &sprite->line_length,
			&sprite->endian);
}
