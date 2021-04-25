
#include "reycasting/ft_reycasting.h"

void	check_around_02plr(t_game *opt, const size_t *str_sizes, size_t i,
	size_t j)
{
	const char	**map;
	size_t		k;
	char		around_symbs[4];

	map = (const char **)opt->world_map;
	if (j == 0 || j == *(str_sizes + 1) - 1)
	{
		printf("Error: map parse\n");
		exit(2);
	}
	if (j > *(str_sizes + 0) - 1 || j > *(str_sizes + 2) - 1)
	{
		printf("Error: map parse\n");
		exit(2);
	}
	around_symbs[0] = *(*(map + i) + j - 1);
	around_symbs[1] = *(*(map + i) + j + 1);
	around_symbs[2] = *(*(map + i - 1) + j);
	around_symbs[3] = *(*(map + i + 1) + j);
	k = 0;
	while (k < 4)
	{
		if (!ft_memchr("012NSWE", around_symbs[k], 7))
		{
			printf("Error: map parse\n");
			exit(2);
		}
		k++;
	}
}

static void	select_player_direction(t_vector *plr, const char c)
{
	if (c == 'N')
	{
		plr->v_x = -1;
		plr->v_y = 0;
	}
	else if (c == 'S')
	{
		plr->v_x = 1;
		plr->v_y = 0;
	}
	else if (c == 'W')
	{
		plr->v_x = 0;
		plr->v_y = -1;
	}
	else
	{
		plr->v_x = 0;
		plr->v_y = 1;
	}
}

static void	select_camera_plane(t_pos *plr, const char c)
{
	if (c == 'N')
	{
		plr->plane_x = 0;
		plr->plane_y = 0.66;
	}
	else if (c == 'S')
	{
		plr->plane_x = 0;
		plr->plane_y = -0.66;
	}
	else if (c == 'W')
	{
		plr->plane_x = -0.66;
		plr->plane_y = 0;
	}
	else
	{
		plr->plane_x = 0.66;
		plr->plane_y = 0;
	}
}

void	save_player_position(t_game *opt, const char c, const size_t x,
	const size_t y)
{
	if (opt->pos.pos_x > 0)
	{
		printf("Error: plr pos\n");
		exit(16);
	}
	opt->pos.pos_x = (double)x + 0.5;
	opt->pos.pos_y = (double)y + 0.5;
	select_player_direction(&opt->vector, c);
	select_camera_plane(&opt->pos, c);
}
