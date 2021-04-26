/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_hook_handle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 11:50:09 by brice             #+#    #+#             */
/*   Updated: 2021/04/21 11:53:24 by brice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_reycasting.h"

int	key_hook_p(int keycode, t_game *img)
{
	if (keycode == 65307 || keycode == 53)
		ft_print_error(img, "Good bye\n", 26);
	if (keycode == 'd' || keycode == 2)
		img->flags |= M_R;
	if (keycode == 'a' || keycode == 0)
		img->flags |= M_L;
	if (keycode == 'w' || keycode == 13)
		img->flags |= M_F;
	if (keycode == 's' || keycode == 1)
		img->flags |= M_B;
	if (keycode == 65361 || keycode == 123)
		img->flags |= R_L;
	if (keycode == 65363 || keycode == 124)
		img->flags |= R_R;
	return (1);
}

int	key_hook_r(int keycode, t_game *img)
{
	if (keycode == 'd' || keycode == 2)
		img->flags ^= M_R;
	if (keycode == 'a' || keycode == 0)
		img->flags ^= M_L;
	if (keycode == 'w' || keycode == 13)
		img->flags ^= M_F;
	if (keycode == 's' || keycode == 1)
		img->flags ^= M_B;
	if (keycode == 65361 || keycode == 123)
		img->flags ^= R_L;
	if (keycode == 65363 || keycode == 124)
		img->flags ^= R_R;
	return (1);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
