/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reycasting.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 18:06:39 by brice             #+#    #+#             */
/*   Updated: 2021/04/21 12:21:20 by brice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_REYCASTING_H
# define FT_REYCASTING_H
# include "../my_cube.h"
# include "../libft/libft.h"

void	ft_rc_s_first(t_game *img, double *z_buffer);
void	ft_rc_hit(t_game *img);
void	ft_base_rc_value(t_game	*img);
void	ft_calc_step_init_side(t_game *img);
void	ft_vertical_line(t_game *img, int draw_start,
			int draw_end, int color);
void	ft_print_texture(t_game *game);
void	ft_print_sidet(t_game *game, t_data *texture, int y);
void	ft_select_texture(t_game *game, t_data *s_tex);
void	ft_control_plr(t_game *img);
void	move_forward(t_game *img, double move_speed);
void	move_backward(t_game *img, double move_speed);
void	move_left(t_game *img, double move_speed);
void	move_right(t_game *img, double move_speed);
void	turn_player_vector(t_game *img, int k);
void	ft_init_val(t_game *img);
void	ft_texture(t_data *texture, t_game *img, char *str);
void	ft_sprite(t_sprite *sprite, t_game *img, char *str);
void	ft_sort_sprites(int *order, double *dist, int size);
int		key_hook_p(int keycode, t_game *img);
int		key_hook_r(int keycode, t_game *img);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	ft_print_sprite(t_game *img, int draw_end_x, double transform_y,
			const double *z_buffer);
void	ft_calculate_fs(t_game *img, t_sprite *sprite,
			const int *sprite_order, int *i);

#endif