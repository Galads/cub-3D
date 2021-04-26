/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main3D.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 08:52:43 by brice             #+#    #+#             */
/*   Updated: 2021/04/23 09:50:30 by brice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reycasting/ft_reycasting.h"

void 	ft_calculate_sprites(t_game *img, double *z_buffer,
		const int *sprite_order, int *i)
{
	int	draw_start_x;
	int	draw_end_x;

	ft_calculate_fs(img, img->sp, sprite_order, i);
	img->sprite.sprite_height = abs((int)(img->img.height
				/ (img->sprite.transform_y)));
	img->sprite.draw_start_y = -img->sprite.sprite_height / 2
		+ img->img.height / 2;
	if (img->sprite.draw_start_y < 0)
		img->sprite.draw_start_y = 0;
	img->sprite.draw_end_y = img->sprite.sprite_height / 2
		+ img->img.height / 2;
	if (img->sprite.draw_end_y >= img->img.height)
		img->sprite.draw_end_y = img->img.height - 1;
	img->sprite.sprite_width = abs((int)(img->img.height
				/ (img->sprite.transform_y)));
	draw_start_x = -img->sprite.sprite_width / 2 + img->sprite.sprite_screen_x;
	if (draw_start_x < 0)
		draw_start_x = 0;
	draw_end_x = img->sprite.sprite_width / 2 + img->sprite.sprite_screen_x;
	if (draw_end_x >= img->img.width)
		draw_end_x = img->img.width - 1;
	img->sprite.stripe = draw_start_x;
	ft_print_sprite(img, draw_end_x, (img->sprite.transform_y), z_buffer);
	(*i)++;
}

void	ft_reycasting_simple(t_game *img)
{
	int	i;

	i = 0;
	ft_rc_s_first(img, img->sprite.z_buffer);
	while (i < img->sprite.count)
	{
		img->sprite.sprite_order[i] = i;
		img->sprite.sprite_distance[i] = (pow((img->rc.pos_x - img->sp[i].x), 2)
				+ pow((img->rc.pos_y - img->sp[i].y), 2));
		i++;
	}
	ft_sort_sprites(img->sprite.sprite_order, img->sprite.sprite_distance,
		(int)img->sprite.count);
	i = 0;
	while (i < img->sprite.count)
		 ft_calculate_sprites(img, img->sprite.z_buffer,
			 img->sprite.sprite_order, &i);
}

int	render_frame(t_game *img)
{
	img->img.img = mlx_new_image(img->img.mlx, img->img.width, img->img.height);
	img->img.addr = mlx_get_data_addr(img->img.img, &img->img.bits_per_pixel,
			&img->img.line_length, &img->img.endian);
	ft_reycasting_simple(img);
	ft_control_plr(img);
	mlx_put_image_to_window(img->img.mlx, img->img.win,
		img->img.img, 0, 0);
	if (img->flag_screen == 2)
	{
		ft_screen_shot(img);
		mlx_destroy_image(img->img.mlx, img->img.img);
		exit(1);
	}
	else
		mlx_destroy_image(img->img.mlx, img->img.img);
	return (1);
}

void	ft_basic_while(t_game *img)
{
	mlx_hook(img->img.win, 2, 1L << 0, &key_hook_p, img);
	mlx_hook(img->img.win, 3, 1L << 1, &key_hook_r, img);
	ft_texture(&img->texture_n, img, img->texture_n.relative_path);
	ft_texture(&img->texture_e, img, img->texture_e.relative_path);
	ft_texture(&img->texture_s, img, img->texture_s.relative_path);
	ft_texture(&img->texture_w, img, img->texture_w.relative_path);
	ft_sprite(&img->sprite, img, img->sprite.relative_path);
	mlx_loop_hook(img->img.mlx, &render_frame, img);
	mlx_do_sync(img->img.mlx);
	mlx_loop(img->img.mlx);
}

int	main(int argc, char **argv)
{
	t_game	img;
	char	*line;

	if (argc == 1)
		ft_print_error(&img, "no argument map", 1);
	line = ft_strnstr(argv[1], ".cub", INT_MAX2);
	if (!line)
		ft_print_error(&img, "\"Error: no find file with expansion"
			"\\\".cub 1\\\"\\n\"", 1);
	if (*line && argc == 2)
	{
		img.flag_screen = 1;
		ft_parser(argc, argv, &img);
		map_parser(&img);
		ft_init_val(&img);
		ft_basic_while(&img);
	}
	else if (*line && argc == 3 && !ft_strncmp(argv[2], "--save", INT_MAX2))
	{
		img.flag_screen = 2;
		ft_parser(argc, argv, &img);
		ft_init_val(&img);
		ft_basic_while(&img);
	}
	return (0);
}
