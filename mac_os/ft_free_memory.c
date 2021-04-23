/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 09:53:02 by brice             #+#    #+#             */
/*   Updated: 2021/04/23 09:53:46 by brice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_cube.h"

void	ft_free_memory(t_game *img)
{
	int	i;

	i = 0;
//	free(img->texture_n.relative_path);
//	free(img->texture_s.relative_path);
//	free(img->texture_w.relative_path);
//	free(img->texture_e.relative_path);
	free(img->sprite.z_buffer);
	free(img->sprite.sprite_order);
	free(img->sprite.sprite_distance);
	while (i < img->sprite.count)
		free(img->sp[i++].relative_path);
	free(img->sp);
	mlx_destroy_image(img->img.mlx, img->texture_e.img);
	mlx_destroy_image(img->img.mlx, img->texture_s.img);
	mlx_destroy_image(img->img.mlx, img->texture_n.img);
	mlx_destroy_image(img->img.mlx, img->texture_w.img);
	mlx_destroy_image(img->img.mlx, img->sprite.img);
	i = 0;
	while (i < img->map_height + 1)
		free(img->world_map[i++]);
	free(img->world_map);
	mlx_destroy_window(img->img.mlx, img->img.win);
}
