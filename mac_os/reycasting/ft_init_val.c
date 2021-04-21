/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_val.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 11:45:43 by brice             #+#    #+#             */
/*   Updated: 2021/04/21 11:49:43 by brice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_reycasting.h"

void	ft_init_val(t_game *img)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	img->sprite.count = 0;
	while (img->world_map[i] && i < img->map_height)
	{
		while (img->world_map[i][j])
		{
			if (img->world_map[i][j] == 'N' || img->world_map[i][j] == 'S'
				|| img->world_map[i][j] == 'W' || img->world_map[i][j] == 'E')
			{
				img->pos.pos_x = i;
				img->pos.pos_y = j;
			}
			if (img->world_map[i][j] == '2')
				img->sprite.count++;
			j++;
		}
		j = 0;
		i++;
	}
	i = 0;
	j = 0;
	img->sp = (t_sprite *)ft_calloc(img->sprite.count, sizeof (t_sprite));
	while (img->world_map[i] && i < img->map_height)
	{
		while (img->world_map[i][j])
		{
			if (img->world_map[i][j] == '2')
			{
				img->sp[k].x = i;
				img->sp[k].y = j;
				img->sp[k].x += 0.5;
				img->sp[k].y += 0.5;
				k++;
			}
			j++;
		}
		j = 0;
		i++;
	}
	img->pos.pos_x += 0.5;
	img->pos.pos_y += 0.5;
	img->flags = 0;
	img->pos.plane_x = 0;
	img->pos.plane_y = 0.66;
	img->vector.v_x = -0.99;
	img->vector.v_y = 0;
	img->sprite.x += 0.5;
	img->sprite.y += 0.5;
	img->img.mlx = mlx_init();
	img->img.win = mlx_new_window(img->img.mlx, img->img.width,
			img->img.height, "CUB3D");
}

void	ft_sort_sprites(int *order, const double *dist, int size)
{
	int	i;
	int	j;
	int	temp;

	i = 0;
	j = 1;
	while (i < size)
	{
		while (j < size)
		{
			if (dist[j - 1] < dist[j])
			{
				temp = order[j - 1];
				order[j - 1] = order[j];
				order[j] = temp;
				j++;
			}
			else
				return ;
		}
		j = 0;
		i++;
	}
}
