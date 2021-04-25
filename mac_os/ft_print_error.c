#include "my_cube.h"

void ft_print_error(t_game *img, char *str, int code)
{
	int i;

	i = 0;
	if (img->texture_n.relative_path)
		free(img->texture_n.relative_path);
	if (img->texture_s.relative_path)
		free(img->texture_s.relative_path);
	if (img->texture_e.relative_path)
		free(img->texture_e.relative_path);
	if (img->texture_w.relative_path)
		free(img->texture_w.relative_path);
	if (img->sprite.z_buffer)
		free(img->sprite.z_buffer);
	if (img->sprite.sprite_order)
		free(img->sprite.sprite_order);
	if (img->sprite.sprite_distance)
		free(img->sprite.sprite_distance);
	if (i < img->sprite.count)
	{
		free(img->sp[i++].relative_path);
		free(img->sp);
	}
	if (img->texture_e.img)
		mlx_destroy_image(img->img.mlx, img->texture_e.img);
	if (img->texture_s.img)
		mlx_destroy_image(img->img.mlx, img->texture_s.img);
	if (img->texture_n.img)
		mlx_destroy_image(img->img.mlx, img->texture_n.img);
	if (img->texture_w.img)
		mlx_destroy_image(img->img.mlx, img->texture_w.img);
	if (img->sprite.img)
		mlx_destroy_image(img->img.mlx, img->sprite.img);
	i = 0;
	if (i < img->map_height)
	{
		while (i < img->map_height + 1)
			free(img->world_map[i++]);
		free(img->world_map);
	}
	if (img->img.win)
		mlx_destroy_window(img->img.mlx, img->img.win);
	printf("Error: %s", str);
	exit(code);
}