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
	if (!ft_strncmp(*result, "R", INT_MAX) && !(img->flag_control & RES))
	{
		img->flag_parser |= RES;
		printf("set R\n");
	}
	else if (!ft_strncmp(*result, "S", INT_MAX) && !(img->flag_control & S))
		img->flag_parser |= S;
	else if (!ft_strncmp(*result, "NO", INT_MAX) && !(img->flag_control & NO))
		img->flag_parser |= NO;
	else if (!ft_strncmp(*result, "SO", INT_MAX) && !(img->flag_control & SO))
		img->flag_parser |= SO;
	else if (!ft_strncmp(*result, "WE", INT_MAX) && !(img->flag_control & WE))
		img->flag_parser |= WE;
	else if (!ft_strncmp(*result, "EA", INT_MAX) && !(img->flag_control & EA))
		img->flag_parser |= EA;
	else if (!ft_strncmp(*result, "F", INT_MAX) && !(img->flag_control & F))
		img->flag_parser |= F;
	else if (!ft_strncmp(*result, "C", INT_MAX) && !(img->flag_control & C))
		img->flag_parser |= C;
	else
	{
		printf("Error header");
		exit(1);
	}
}

void	ft_parse_str(const char **result, t_game *img)
{
	if (img->flag_parser & RES && result[1] && result[2] && !result[3])
	{
		img->img.height = ft_atoi(result[1]);
		img->img.width = ft_atoi(result[2]);
		img->j_ps++;
	}
	else if (img->flag_parser & S && result[1] && !result[2])
	{
		img->sprite.relative_path = ft_strdup((char *)result[1]);
		img->j_ps++;
	}
	else if (img->flag_parser & NO && result[1] && !result[2])
	{
		img->texture_n.relative_path = ft_strdup((char *)result[1]);
		img->j_ps++;
	}
	else if (img->flag_parser & SO && result[1] && !result[2])
	{
		img->texture_s.relative_path = ft_strdup((char *)result[1]);
		img->j_ps++;
	}
	else if (img->flag_parser & WE && result[1] && !result[2])
	{
		img->texture_w.relative_path = ft_strdup((char *)result[1]);
		img->j_ps++;
	}
	else if (img->flag_parser & EA && result[1] && !result[2])
	{
		img->texture_e.relative_path = ft_strdup((char *)result[1]);
		img->j_ps++;
	}
	else if (img->flag_parser & F  && *result[2] ==',' && *result[4] == ','
			&& ft_isaint(ft_atoi(&*(result)[1]))
			&& ft_isaint(ft_atoi(&(*result)[3]))
			&& ft_isaint(ft_atoi(&*(result)[5])))
	{
		img->rc.col_f = ft_create_trgb(0, ft_atoi(result[1]), ft_atoi(result[3]),
									   ft_atoi(result[5]));
		img->j_ps++;
		printf("\t \t \t hello no color");
	}
	else if (img->flag_parser & C && ft_isaint(ft_atoi(&*(result)[1])) &&
			ft_isaint(ft_atoi(&(*result)[3])) && ft_isaint(ft_atoi(&*(result)[5])))
	{
		img->rc.col_c = ft_create_trgb(0,
			ft_atoi(result[1]),ft_atoi(result[3]),
			ft_atoi(result[5]));
		img->j_ps++;
	}
	else
	{
		printf("Warning: maybe map not a valid\n");
//		exit(1);
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
	if (img->img.height && img->img.width && !(img->flag_control & RES))
		img->flag_control |= RES;
	else if (img->sprite.relative_path && !(img->flag_control & S))
		img->flag_control |= S;
	else if (img->texture_n.relative_path && !(img->flag_control & NO))
		img->flag_control |= NO;
	else if (img->texture_s.relative_path && !(img->flag_control & SO))
		img->flag_control |= SO;
	else if (img->texture_w.relative_path && !(img->flag_control & WE))
		img->flag_control |= WE;
	else if (img->texture_e.relative_path && !(img->flag_control & EA))
		img->flag_control |= EA;
	else if (img->rc.col_f != -1 && !(img->flag_control & F))
		img->flag_control |= F;
	else if (img->rc.col_c != -1 && !(img->flag_control & C))
		img->flag_control |= C;
	else
	{
		printf("Error: many count headers elements\n");
		exit(1);
	}
}

void	ft_free_split(char **line)
{
	int i;

	i = 0;
	while (line[i])
		free(line[i++]);
	free(line);
}

void	ft_check_num(t_game *img)
{
	if (!img->img.height || !img->img.width || !img->sprite.relative_path
	|| !img->texture_e.relative_path || !img->texture_w.relative_path
	|| !img->texture_n.relative_path || !img->texture_s.relative_path
	|| img->rc.col_f == -1 || img->rc.col_c == -1)
	{
		printf("Error: not a valid header");
		exit(1);
	}
}

void	ft_handler_f_c(int *col, char **result)
{
	int i;
	int j;
	int k;
	int rgb[3];

	i = 0;
	j = 1;
	k = 0;
	while (result[i])
	{
		while (result[i][j])
		{
			if (result[i][j] == ' ' || result[i][j] == 'F' || result[i][j] == 'C')
				j++;
			else if (ft_isdigit(result[i][j]))
			{
				rgb[k++] = ft_atoi(&result[i][j]);
				break;
			}
		}
		j = 0;
		i++;
	}
	*col = ft_create_trgb(0, rgb[0], rgb[1], rgb[2]);
}

int	ft_check_addr_mem(char *result, char c)
{
	int i;
	char *r_s = NULL;

	i = 0;
	while (result[i])
	{
		if (result[i] == c)
			r_s = &(result[i]);
		if (result[i] >= '0' && result[i] <= '9' && r_s != NULL)
		{
			if (r_s < (&result[i]))
				return (1);
		}
		i++;
	}
	return (0);
}

int	ft_check_str_num(char **result)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	while (i < ft_strlen(result[0]))
	{
		if (result[0][i] >= '0' && result[0][i] <= '9')
		{
			while (result[0][i] != ' ' && result[0][i] != ',' && result[0][i] != '\0')
			{
				if (j > 4)
					return (0);
				j++;
				i++;
			}
			k++;
		}
		if (result[0][i] == ' ' || result[0][i] == ',')
			j = 0;
		if ((k == 3 && (result[0][i] > 0 && result[0][i] < 32)) ||
		(k == 3 && (result[0][i] > 32 && result[0][i] <= 127)))
			k++;
		if (k > 3)
			return (-1);
		i++;
	}
	return (1);
}

void	ft_parse_head(char **line, t_game *img)
{
	char **result;
	int i;

	i = 0;

	result = ft_split(*line, ' ');
	if (*result)
	{
		if (!ft_strncmp(result[0], "F", INT_MAX) || !ft_strncmp(result[0], "C", INT_MAX))
		{
			while (result[i])
				result[i++];
			int a = ft_check_str_num(line);
			if (a < 0 || a == 0)
				return;
			if ((i <= 6 && !ft_strncmp(result[0], "F", INT_MAX) || i <= 6
			&& !ft_strncmp(result[0], "C", INT_MAX)) && ft_check_str_num(line))
			{
				ft_free_split(result);
				result = ft_split(*line, ',');
				i = 0;
				while (result[i])
					result[i++];
				if (i == 3)
				{
					if (ft_check_addr_mem(result[0], 'F'))
					{
						ft_handler_f_c(&img->rc.col_f, result);
						img->j_ps++;
					}
					else if(ft_check_addr_mem(result[0], 'C'))
					{
						ft_handler_f_c(&img->rc.col_c, result);
						img->j_ps++;
					}

				}
				ft_free_split(result);
				return;
			}
		}
	}
i = 0;
	while (result[i] && i < 1)
	{
		ft_parse_t_a_s(result, img);
		ft_parse_str(result, img);
		ft_fill_flag(img);
		img->flag_parser = 0;
		i++;
	}
	ft_free_split(result);
}

void	ft_init_parser(t_game *img)
{
	img->flag_parser = 0;
	img->flag_control = 0;
	img->rc.col_c = -1;
	img->rc.col_f = -1;
	img->img.width = 0;
	img->img.height = 0;
	img->sprite.relative_path = 0;
	img->texture_s.relative_path = 0;
	img->texture_n.relative_path = 0;
	img->texture_e.relative_path = 0;
	img->texture_w.relative_path = 0;
	img->map_width = 0;
	img->map_height = 0;
	img->j_ps = 0;
}

void	ft_fill_map(t_game *img, t_list **list_head)
{
	t_list	*list;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	list = *list_head;

	img->world_map = (char **)ft_calloc(img->map_height + 1, sizeof (char *));
	while (i < img->map_height)
		img->world_map[i++] = (char *)ft_calloc(img->map_width, sizeof (char));
	i = 0;
	while (i < img->map_height && list)
	{
		k = ft_strlen(list->content);
		ft_strlcpy(img->world_map[i], list->content, k + 1);
		i++;
		list = list->next;
	}
	ft_lstclear(list_head, &free);
}

void ft_check_line(char **line, t_list **list_head, t_list **list)
{
	int k;
	int flag;
	int k5;

	flag = 1;
	k =  ft_valid_line(line);
	k5 = k;
	if((*line)[k] && (*line)[k] != '1')
	{
		free(*line);
		printf("Error :  invalid header\n");
		exit(45);
	}
	while ((*line)[k])
	{
		if (ft_memchr("1 ", (*line)[k], 2))
			if (!*list_head)
			{
				*list_head = ft_lstnew(*line);
				flag = 0;
			}
		k++;
	}
	if (flag == 1 && (*line)[k5])
	{
		*list = ft_lstnew(*line);
		ft_lstadd_back(list_head, *list);
	}
	else if (!(*line)[k5])
		free(*line);
}

void	ft_parse_tail(t_game *img, char **line, const int *fd)
{
	int	i;
	t_list *list_head = NULL;
	t_list *list = NULL;

	i = 1;
	while (i >= 0)
	{
		i = get_next_line(*fd, line);
		ft_check_line(line, &list_head, &list);
		if (i == 0)
			break;
	}
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
	int		i;
	int		fd;
	char	*line;

	i = 1;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		printf("Error: %s", strerror(errno));
		exit(1);
	}
	ft_init_parser(img);
	if (!argv[1])
		printf("Error: no map\n");
	while ((i > 0) && img->j_ps < 8)
	{
		i = get_next_line(fd, &line);
		printf("|%s|\n", line);
		if (*line != '\0' && *line != '\n' && img->j_ps < 8)
			ft_parse_head(&line, img);
		if (i == 1)
			free(line);
	}
	if (img->j_ps != 8)
	{
		printf("Error: parse header\n");
		exit(33);
	}
	ft_check_num(img);
	ft_parse_tail(img, &line, &fd);
}
