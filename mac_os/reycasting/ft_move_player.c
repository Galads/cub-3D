/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 11:54:18 by brice             #+#    #+#             */
/*   Updated: 2021/04/21 11:58:54 by brice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_reycasting.h"

void	move_forward(t_game *img, double move_speed)
{
	if (img->world_map[(int)(img->pos.pos_x + img->vector.v_x * move_speed)]
		[(int)(img->pos.pos_y)] != '1')
		img->pos.pos_x += img->vector.v_x * move_speed;
	if (img->world_map[(int)(img->pos.pos_x)]
		[(int)(img->pos.pos_y + img->vector.v_y * move_speed)] != '1')
		img->pos.pos_y += img->vector.v_y * move_speed;
}

void	move_backward(t_game *img, double move_speed)
{
	if (img->world_map[(int)(img->pos.pos_x - img->vector.v_x
			* move_speed)][(int)(img->pos.pos_y)] != '1')
		img->pos.pos_x -= img->vector.v_x * move_speed;
	if (img->world_map[(int)(img->pos.pos_x)][(int)(img->pos.pos_y
				- img->vector.v_y * move_speed)] != '1')
		img->pos.pos_y -= img->vector.v_y * move_speed;
}

void	move_left(t_game *img, double move_speed)
{
	if (img->world_map[(int)(img->pos.pos_x - img->vector.v_y
			* move_speed)][(int)(img->pos.pos_y)] != '1')
		img->pos.pos_x -= img->pos.plane_x * move_speed;
	if (img->world_map[(int)(img->pos.pos_x)][(int)(img->pos.pos_y
				+ img->vector.v_x * move_speed)] != '1')
		img->pos.pos_y -= img->pos.plane_y * move_speed;
}

void	move_right(t_game *img, double move_speed)
{
	if (img->world_map[(int)(img->pos.pos_x + img->vector.v_y
			* move_speed)][(int)(img->pos.pos_y)] != '1')
		img->pos.pos_x += img->pos.plane_x * move_speed;
	if (img->world_map[(int)(img->pos.pos_x)][(int)(img->pos.pos_y
				- img->vector.v_x * move_speed)] != '1')
		img->pos.pos_y += img->pos.plane_y * move_speed;
}

void	turn_player_vector(t_game *img, int k)
{
	double	rot_speed;
	double	old_plane_x;
	double	old_dir_x;

	old_plane_x = img->pos.plane_x;
	old_dir_x = img->vector.v_x;
	rot_speed = 0.05;
	img->vector.v_x = img->vector.v_x * cos(k * rot_speed)
		- img->vector.v_y * sin(k * rot_speed);
	img->vector.v_y = old_dir_x * sin(k * rot_speed)
		+ img->vector.v_y * cos(k * rot_speed);
	img->pos.plane_x = img->pos.plane_x * cos(k * rot_speed)
		- img->pos.plane_y * sin(k * rot_speed);
	img->pos.plane_y = old_plane_x * sin(k * rot_speed)
		+ img->pos.plane_y * cos(k * rot_speed);
}
