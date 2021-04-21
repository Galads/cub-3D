/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_control_plr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 11:45:01 by brice             #+#    #+#             */
/*   Updated: 2021/04/21 11:45:27 by brice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_reycasting.h"

void	ft_control_plr(t_game *img)
{
	double	move_speed;

	move_speed = 0.1315;
	if (img->flags & M_F)
		move_forward(img, move_speed);
	if (img->flags & M_B)
		move_backward(img, move_speed);
	if (img->flags & M_R)
		move_right(img, move_speed);
	if (img->flags & M_L)
		move_left(img, move_speed);
	if (img->flags & R_R)
		turn_player_vector(img, -1);
	if (img->flags & R_L)
		turn_player_vector(img, 1);
}
