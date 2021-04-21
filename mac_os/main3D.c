#include "reycasting/ft_reycasting.h"
#include "my_cube.h"

void 	ft_calculate_sprites(t_game *img, t_sprite *sprite,
						   double *ZBuffer, const int *sprite_order,int *i)
{
	int	draw_start_x;
	int	draw_end_x;

	ft_calculate_fs(img, sprite, sprite_order, i);
	img->sprite.sprite_height = abs((int)(img->img.height /
			(img->sprite.transform_y)));
	img->sprite.draw_start_y = -img->sprite.sprite_height / 2 +
			img->img.height / 2;
	if(img->sprite.draw_start_y < 0)
		img->sprite.draw_start_y = 0;
	img->sprite.draw_end_y = img->sprite.sprite_height / 2 +
			img->img.height / 2;
	if(img->sprite.draw_end_y >= img->img.height)
		img->sprite.draw_end_y = img->img.height - 1;
	img->sprite.sprite_width= abs((int) (img->img.height /
			(img->sprite.transform_y)));
	draw_start_x = -img->sprite.sprite_width / 2 + img->sprite.sprite_screen_x;
	if(draw_start_x < 0)
		draw_start_x = 0;
	draw_end_x = img->sprite.sprite_width / 2 + img->sprite.sprite_screen_x;
	if(draw_end_x >= img->img.width)
		draw_end_x = img->img.width - 1;
	img->sprite.stripe = draw_start_x;
	ft_print_sprite(img, draw_end_x, (img->sprite.transform_y), ZBuffer);
	(*i)++;
}

void	ft_reycasting_simple(t_game *img)
{
	double	sprite_distance[img->sprite.count];
	int		spriteOrder[img->sprite.count];
	double	z_buffer[img->img.width];
	int i;

	i = 0;
	ft_rc_s_first(img, z_buffer);
	while (i < img->sprite.count)
	{
		spriteOrder[i] = i;
		sprite_distance[i] = (pow((img->rc.pos_x - img->sp[i].x), 2)
							+ pow((img->rc.pos_y - img->sp[i].y), 2));
		i++;
	}
	ft_sort_sprites(spriteOrder, sprite_distance, (int)img->sprite.count);
	i = 0;
	while (i < img->sprite.count)
		 ft_calculate_sprites(img, img->sp, z_buffer, spriteOrder, &i);
}

void	render_frame(t_game *img)
{
	img->img.img = mlx_new_image(img->img.mlx, img->img.width, img->img.height);
	img->img.addr = mlx_get_data_addr(img->img.img, &img->img.bits_per_pixel,
									  &img->img.line_length,
									  &img->img.endian);
	ft_reycasting_simple(img);
	ft_control_plr(img);
	mlx_put_image_to_window(img->img.mlx, img->img.win,
						 img->img.img, 0, 0);
	mlx_destroy_image(img->img.mlx, img->img.img);
}

void ft_basic_while(t_game *img)
{
	mlx_hook(img->img.win, 2, 1L << 0, &key_hook_p, img);
	mlx_hook(img->img.win, 3, 1L << 1, &key_hook_r, img);

//		ft_texture(&img.texture_n, &img, img.texture_n.relative_path);
//		ft_texture(&img.texture_e, &img, img.texture_e.relative_path);
//		ft_texture(&img.texture_s, &img,img.texture_s.relative_path);
//		ft_texture(&img.texture_w, &img,img.texture_w.relative_path);

	ft_texture(&img->texture_n, img, "/Users/brice/Desktop/ft_parser/mac_os/textures/bluestone.xpm");
	ft_texture(&img->texture_e, img, "/Users/brice/Desktop/ft_parser/mac_os/textures/eagle.xpm");
	ft_texture(&img->texture_s, img,"/Users/brice/Desktop/ft_parser/mac_os/textures/redbrick.xpm");
	ft_texture(&img->texture_w, img, "/Users/brice/Desktop/ft_parser/mac_os/textures/purplestone.xpm");
	ft_sprite(&img->sprite, img, "/Users/brice/Desktop/ft_parser/mac_os/sprites/1_1.xpm");

	mlx_loop_hook(img->img.mlx, &render_frame, img);
	mlx_do_sync(img->img.mlx);
	mlx_loop(img->img.mlx);
}

int main(int argc, char **argv)
{
	t_game	img;
	char	*line;

	line = ft_strnstr(argv[1], ".cub", INT_MAX);
	if (line)
	{
		ft_parser(argc, argv, &img);
		ft_init_val(&img);
		ft_basic_while(&img);
	}
	else
		printf("Error: no find file with expansion \".cub\"\n");
	return 0;
}