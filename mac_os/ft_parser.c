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
}

void	ft_parse_str(const char **result, t_game *img)
{
	if (img->flag_parser & RES && result[1] && result[2] && !result[3])
	{
		img->img.height = ft_atoi(result[1]);
		img->img.width = ft_atoi(result[2]);
	}
	else if (img->flag_parser & S && result[1] && !result[2])
		img->sprite.relative_path = ft_strdup((char *)result[1]);
	else if (img->flag_parser & NO && result[1] && !result[2])
	{
		img->texture_n.relative_path = ft_strdup((char *)result[1]);
	}
	else if (img->flag_parser & SO && result[1] && !result[2])
		img->texture_s.relative_path = ft_strdup((char *)result[1]);
	else if (img->flag_parser & WE && result[1] && !result[2])
		img->texture_w.relative_path = ft_strdup((char *)result[1]);
	else if (img->flag_parser & EA && result[1] && !result[2])
		img->texture_e.relative_path = ft_strdup((char *)result[1]);
	else if (img->flag_parser & F  && *result[2] ==',' && *result[4] == ','
			&& ft_isaint(ft_atoi(&*(result)[1]))
			&& ft_isaint(ft_atoi(&(*result)[3]))
			&& ft_isaint(ft_atoi(&*(result)[5])))
	{
		img->rc.col_f = ft_create_trgb(0, ft_atoi(result[1]), ft_atoi(result[3]),
									   ft_atoi(result[5]));
		printf("\t \t \t hello no color");
	}
	else if (img->flag_parser & C && ft_isaint(ft_atoi(&*(result)[1])) &&
			ft_isaint(ft_atoi(&(*result)[3])) && ft_isaint(ft_atoi(&*(result)[5])))
		img->rc.col_c = ft_create_trgb(0, ft_atoi(result[1]), ft_atoi(result[3]),
									   ft_atoi(result[5]));
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
	if (img->img.height && img->img.width)
		img->flag_control |= RES;
	if (img->sprite.relative_path)
		img->flag_control |= S;
	if (img->texture_n.relative_path)
		img->flag_control |= NO;
	if (img->texture_s.relative_path)
		img->flag_control |= SO;
	if (img->texture_w.relative_path)
		img->flag_control |= WE;
	if (img->texture_e.relative_path)
		img->flag_control |= EA;
	if (img->rc.col_f != -1)
		img->flag_control |= F;
	if (img->rc.col_c != -1)
		img->flag_control |= C;
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
//			j++;
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
//		printf("\t\t\tHELLLLOOOO\n");
//		printf("\t\t\tresult: %s\n", result[2]);

		if (!ft_strncmp(result[0], "F", INT_MAX) || !ft_strncmp(result[0], "C", INT_MAX))
		{
			while (result[i])
				result[i++];
			int a = ft_check_str_num(line);
			if (a < 0 || a == 0)
				return;
			printf("str num |%d|", a);
			if ((i <= 6 && !ft_strncmp(result[0], "F", INT_MAX) || i <= 6 && !ft_strncmp(result[0], "C", INT_MAX)) && ft_check_str_num(line))
			{
				ft_free_split(result);
				result = ft_split(*line, ',');
				printf("result |%s|\n", result[0]);
				i = 0;
				while (result[i])
					result[i++];
				if (i == 3)
				{
					if (ft_check_addr_mem(result[0], 'F'))
						ft_handler_f_c(&img->rc.col_f, result);
					else if(ft_check_addr_mem(result[0], 'C'))
						ft_handler_f_c(&img->rc.col_c, result);

				}
				ft_free_split(result);
				return;
			}
		}
	}
i = 0;
	printf("\nreturn color c : |%d|\n", img->rc.col_c);
	while (result[i])
	{
		ft_parse_t_a_s(result, img);
		ft_parse_str(result, img);
		ft_fill_flag(img);
		img->flag_parser = 0;
		i++;
	}
//	ft_check_num(img);
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
		k = ft_strlen(list->content);
		ft_strlcpy(img->world_map[i], list->content, k + 1);
		i++;
		list = list->next;
	}
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
		}
		free(line);
		ft_check_num(img);
		ft_parse_tail(img, &line, &fd);
	}
}
