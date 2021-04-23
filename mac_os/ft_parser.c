#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include "errno.h"
#include "my_cube.h"

int	ft_create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

void ft_parse_t_a_s(const char **result, t_game *img)
{
	if (!ft_strncmp(*result, "R", INT_MAX))
	{
		img->flag_parser |= RES;
		printf("set R\n");
	}
	else if (!ft_strncmp(*result, "S", INT_MAX))
		img->flag_parser |= S;
	else if (!ft_strncmp(*result, "NO", INT_MAX))
		img->flag_parser |= NO;
	else if (!ft_strncmp(*result, "SO", INT_MAX))
		img->flag_parser |= SO;
	else if (!ft_strncmp(*result, "WE", INT_MAX))
		img->flag_parser |= WE;
	else if (!ft_strncmp(*result, "EA", INT_MAX))
		img->flag_parser |= EA;
	else if (!ft_strncmp(*result, "F", INT_MAX))
		img->flag_parser |= F;
	else if (!ft_strncmp(*result, "C", INT_MAX))
		img->flag_parser |= C;
//	else
//		printf("Error: no find res or texture with sprite\n");
}

void	ft_parse_str(const char **result, t_game *img)
{
	if (img->flag_parser & RES && result[1] && result[2] && !result[3])
	{
		img->img.height = ft_atoi(result[1]);
		img->img.width = ft_atoi(result[2]);
		img->flag_parser ^= RES;
	}
	else if (img->flag_parser & S && result[1] && !result[2])
		img->sprite.relative_path = ft_strdup((char *)result[1]);
	else if (img->flag_parser & NO && result[1] && !result[2])
	{
		img->texture_n.relative_path = ft_strdup((char *)result[1]);
		printf("set NO\n");
//		free(img->texture_n.relative_path);
//		printf("1\n");
//		printf("2\n");
	}
	else if (img->flag_parser & SO && result[1] && !result[2])
		img->texture_s.relative_path = ft_strdup((char *)result[1]);
	else if (img->flag_parser & WE && result[1] && !result[2])
		img->texture_w.relative_path = ft_strdup((char *)result[1]);
	else if (img->flag_parser & EA && result[1] && !result[2])
		img->texture_e.relative_path = ft_strdup((char *)result[1]);
	else if (img->flag_parser & F && ft_isaint(ft_atoi(&*(result)[1])) &&
			 ft_isaint(ft_atoi(&(*result)[3])) && ft_isaint(ft_atoi(&*(result)[5])))
		img->rc.col_f = ft_create_trgb(0, ft_atoi(result[1]), ft_atoi(result[3]),
									   ft_atoi(result[5]));
	else if (img->flag_parser & C && ft_isaint(ft_atoi(&*(result)[1])) &&
			ft_isaint(ft_atoi(&(*result)[3])) && ft_isaint(ft_atoi(&*(result)[5])))
		img->rc.col_c = ft_create_trgb(0, ft_atoi(result[1]), ft_atoi(result[3]),
									   ft_atoi(result[5]));
	else
	{
		printf("Error: map not a valid\n");
		exit(1);
	}

}

int	ft_check_flag(t_game *img)
{
	if ((img->flag_control & F && img->flag_control & C && img->flag_control & S
	&& img->flag_control & RES &&img->flag_control & EA && img->flag_control & NO
	&& img->flag_control & SO && img->flag_control & WE))
		return (1);
	else if (img->flag_control)
		printf("Warning: maybe no find res or texture with sprite\n");
	else
	{
		printf("hello");
		exit(1);
	}
}

void ft_fill_flag(t_game *img)
{
	if (img->img.height && img->img.width)
		img->flag_parser ^= RES;
	if (img->sprite.relative_path)
		img->flag_control ^= S;
	if (img->texture_n.relative_path)
		img->flag_control ^= NO;
	if (img->texture_s.relative_path)
		img->flag_control ^= SO;
	if (img->texture_w.relative_path)
		img->flag_control ^= WE;
	if (img->texture_e.relative_path)
		img->flag_control ^= EA;
	if (img->rc.col_f)
		img->flag_control ^= F;
	if (img->rc.col_c)
		img->flag_control ^= C;
}
void	ft_free_split(char **line)
{
	int i;

	i = 0;
	while (line[i])
		free(line[i++]);
	free(line);
}

void	ft_parse_head(char **line, t_game *img)
{
	char **result;
	int i;

	i = 0;

	result = ft_split(*line, ' ');
	while (result[i])
	{
		ft_parse_t_a_s(result, img);
		ft_parse_str(result, img);
		ft_fill_flag(img);
//		break;
		img->flag_parser = 0;
		i++;
	}
//	ft_free_split(result);
//	int i;

	i = 0;
	while (result[i] != '\0')
		free(result[i++]);
	free(result);
//	free(line);
}

void	ft_init_parser(t_game *img)
{
	img->flag_parser = 0;
	img->flag_control = 0;
	img->rc.col_c = 0;
	img->rc.col_f = 0;
	img->img.width = 0;
	img->img.height = 0;
	img->sprite.relative_path = 0;
	img->texture_s.relative_path = 0;
	img->texture_n.relative_path = 0;
	img->texture_e.relative_path = 0;
	img->texture_w.relative_path = 0;
	img->map_width = 0;
	img->map_height = 0;
}

void	ft_fill_map(t_game *img, t_list **list_head)
{
	t_list	*list;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	list = *list_head;

	img->world_map = (char **)ft_calloc(img->map_height + 1, sizeof (char *));
	while (i < img->map_height)
		img->world_map[i++] = (char *)ft_calloc(img->map_width, sizeof (char));
	list = *list_head;
	i = 0;
	while (i < img->map_height && list)
	{
		printf("main_map: |");
		k = ft_strlen(list->content);
		ft_strlcpy(img->world_map[i], list->content, k + 1);
		i++;
		list = list->next;
		printf("|\n");
	}
//	list = *list_head;
//	while (list) {
//		printf("zx : |%s|\n", (char *) list->content);
//		list = list->next;
//	}
//	list = *list_head;
	ft_lstclear(list_head, &free);
}

void	ft_parse_tail(t_game *img, char **line, const int *fd)
{
	int i;
	int j;
	t_list	*list_head = NULL;
	t_list	*list;

	j = 0;
	char *lin;

	lin = ft_valid_line(line);
	if (*lin != '\0' && *lin != '\n' && (ft_check_flag(img) == 1))
		list_head = ft_lstnew(*line);

	while ((i = get_next_line(*fd, line)) > 0)
	{
		if (!list_head)
			list_head = ft_lstnew(*line);
		else
		{
			list = ft_lstnew(*line);
			ft_lstadd_back(&list_head, list);
		}
	}
	list = ft_lstnew(*line);
	ft_lstadd_back(&list_head, list);
	img->map_height = ft_lstsize(list_head);

	list = list_head;
	while (list)
	{
		if (img->map_width < ft_strlen(list->content))
			img->map_width = (int)ft_strlen(list->content);
		list = list->next;
	}
	ft_fill_map(img, &list_head);
}

void	ft_parser(int argc, char **argv, t_game *img)
{
	int		j;
	int		i;
	int		fd;
	char	*line;

	j = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		printf("Error: %s", strerror(errno));
		exit(1);
	}
	ft_init_parser(img);
	if (!argv[1])
		printf("Error: no map\n");
	if (argc == 2 || argc == 3)
	{
		while ((i = get_next_line(fd, &line)) && j <= 7)
		{
			ft_parse_head(&line, img);
			if (*line != '\0')
				j++;
			free(line);
			ft_check_flag(img);
		}
		free(line);
		ft_parse_tail(img, &line, &fd);
//		free(line);
//		exit(1);
	}
}
