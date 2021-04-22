#include "my_cube.h"
void ft_free_memory(t_game *img)
{
	int i;

	i = 0;
	free(img->texture_n.relative_path);
	free(img->texture_s.relative_path);
	free(img->texture_w.relative_path);
	free(img->texture_e.relative_path);

	while (img->world_map[i])
		free(img->world_map[i++]);
}