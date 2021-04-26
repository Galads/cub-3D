/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_val.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 11:45:43 by brice             #+#    #+#             */
/*   Updated: 2021/04/23 08:42:53 by brice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_reycasting.h"

static	void	ft_vectors_init(t_game *img, int *i, int *j)
{
	img->pos.plane_x = 0;
	img->pos.plane_y = 0;
	img->vector.v_x = 0;
	img->vector.v_y = 0;
	if (img->world_map[*i][*j] == 'N')
	{
		img->pos.plane_y = 0.66;
		img->vector.v_x = -0.99;
	}
	else if (img->world_map[*i][*j] == 'S')
	{
		img->pos.plane_y = -0.66;
		img->vector.v_x = 0.99;
	}
	else if (img->world_map[*i][*j] == 'W')
	{
		img->pos.plane_x = 0.66;
		img->vector.v_y = 0.99;
	}
	else if (img->world_map[*i][*j] == 'E')
	{
		img->pos.plane_x = -0.66;
		img->vector.v_y = -0.99;
	}
}

static	void	ft_init_player(t_game *img, int *i, int *j)
{
	while (img->world_map[*i][*j])
	{
		if (img->world_map[*i][*j] == 'N' || img->world_map[*i][*j] == 'S'
			|| img->world_map[*i][*j] == 'W' || img->world_map[*i][*j] == 'E')
		{
			img->pos.pos_x = *i;
			img->pos.pos_y = *j;
			ft_vectors_init(img, i, j);
		}
		if (img->world_map[*i][*j] == '2')
			img->sprite.count++;
		(*j)++;
	}
	(*j) = 0;
	(*i)++;
}

static	void	ft_init_sprite(t_game *img, int *i, int *j, int k)
{
	img->sp = (t_sprite *)ft_calloc(img->sprite.count, sizeof (t_sprite));
	while (img->world_map[*i] && *i < img->map_height)
	{
		while (img->world_map[*i][*j])
		{
			if (img->world_map[*i][*j] == '2')
			{
				img->sp[k].x = *i;
				img->sp[k].y = *j;
				img->sp[k].x += 0.5;
				img->sp[k++].y += 0.5;
			}
			(*j)++;
		}
		(*j) = 0;
		(*i)++;
	}
	img->pos.pos_x += 0.5;
	img->pos.pos_y += 0.5;
	img->flags = 0;
	img->sprite.x += 0.5;
	img->sprite.y += 0.5;
	img->sprite.sprite_distance = ft_calloc(img->sprite.count, sizeof(double));
	img->sprite.z_buffer = ft_calloc(img->img.width, sizeof(double));
	img->sprite.sprite_order = ft_calloc(img->sprite.count, sizeof(int));
}

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
		ft_init_player(img, &i, &j);
	i = 0;
	j = 0;
	ft_init_sprite(img, &i, &j, k);
	img->img.mlx = mlx_init();
	img->img.win = mlx_new_window(img->img.mlx, img->img.width,
			img->img.height, "CUB3D");
}

void	ft_sort_sprites(int *order, double *dist, int size)
{
	int		i;
	int		j;
	int		temp;
	double	temp1;

	i = 0;
	j = 0;
	while (i < size)
	{
		while (j < size)
		{
			j++;
			if (dist[j - 1] < dist[j])
			{
				temp = order[j - 1];
				order[j - 1] = order[j];
				order[j] = temp;
				temp1 = dist[j - 1];
				dist[j - 1] = dist[j];
				dist[j] = temp1;
			}
		}
		j = 0;
		i++;
	}
}
