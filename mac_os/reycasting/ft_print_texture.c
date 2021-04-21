/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 18:56:03 by brice             #+#    #+#             */
/*   Updated: 2021/04/16 19:06:54 by brice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_reycasting.h"

void	ft_print_sidet(t_game *game, t_data *texture, int y)
{
	unsigned int	color;

	color = *(unsigned int *)(texture->addr
			+ (game->rc.tex_y * texture->line_length + game->rc.tex_x
				* (texture->bits_per_pixel / 8)));
	my_mlx_pixel_put(&game->img, game->rc.x, y, (int)color);
}

void	ft_select_texture(t_game *game, t_data *s_tex)
{
	if (game->rc.side == 0 && game->rc.ray_dir_x < 0)
		*s_tex = game->texture_n;
	else if (game->rc.side == 0 && game->rc.ray_dir_x > 0)
		*s_tex = game->texture_s;
	else if (game->rc.side == 1 && game->rc.ray_dir_y > 0)
		*s_tex = game->texture_w;
	else if (game->rc.side == 1 && game->rc.ray_dir_y < 0)
		*s_tex = game->texture_e;
}

void	ft_print_texture(t_game *game)
{
	double	wallX;
	double	step;
	double	texPos;
	int		y;
	t_data	s_tex;

	if (game->rc.side == 0)
		wallX = game->rc.pos_y + game->rc.perp_wall_dist * game->rc.ray_dir_y;
	else
		wallX = game->rc.pos_x + game->rc.perp_wall_dist * game->rc.ray_dir_x;
	wallX -= floor((wallX));
	game->rc.tex_x = (int)(wallX * (double)(texWidth));
	if (game->rc.side == 0 && game->rc.ray_dir_x > 0)
		game->rc.tex_x = texWidth - game->rc.tex_x - 1;
	if (game->rc.side == 1 && game->rc.ray_dir_y < 0)
		game->rc.tex_x = texWidth - game->rc.tex_x - 1;
	step = 1.0 * texHeight / game->rc.line_height;
	texPos = (game->rc.draw_start - (double)game->img.height / 2
			+ (double)game->rc.line_height / 2) * step;
	y = game->rc.draw_start;
	ft_select_texture(game, &s_tex);
	while (y < game->rc.draw_end)
	{
		game->rc.tex_y = (int)texPos & (texHeight - 1);
		texPos += step;
		ft_print_sidet(game, &s_tex, y);
		y++;
	}
}
