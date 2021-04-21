#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
//#include <error.h>
#include "errno.h"
#include "my_cube.h"

int	ft_create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

void ft_parse_t_a_s(const char **result, t_game *img)
{
//	printf("res: %d, sprite: %d\n", (img->flag_parser & RES), (img->flag_parser & S));
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
	}
	else if (img->flag_parser & S && result[1] && !result[2])
		img->sprite.relative_path = ft_strdup((char *)result[1]);
	else if (img->flag_parser & NO && result[1] && !result[2])
		img->texture_n.relative_path = ft_strdup((char *)result[1]);
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
//		printf("result: %s\n", result[0]);
//		free(result);
		exit(1);
	}
	printf("height - |%d|, width - |%d|\n", img->img.height, img->img.width);
//	printf("sprite path - |%s|\n", img->sprite.relative_path);
}

int	ft_check_flag(t_game *img)
{
	if ((img->flag_control & F && img->flag_control & C && img->flag_control & S
	&& img->flag_control & RES &&img->flag_control & EA && img->flag_control & NO
	&& img->flag_control & SO && img->flag_control & WE))
	{
		printf("\t-----------------------ok------------------\t\n");
		return (1);
	}
	else if (img->flag_control)
	{
		printf("Warning: maybe no find res or texture with sprite\n");
//		exit(1);
	}
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
	if (img->rc.col_f)
		img->flag_control |= F;
	if (img->rc.col_c)
		img->flag_control |= C;
}

void	ft_parse_head(char **line, t_game *img)
{
	char **result;
	int i;

	i = 0;

	result = ft_split(*line, ' ');
	while (result[i])
	{
		ft_parse_t_a_s((const char **) result, img);
		ft_parse_str(result, img);
		ft_fill_flag(img);
		img->flag_parser = 0;
//		printf("->|%s|<-\n", result[i]);
		i++;
	}
//	printf("height - |%d|, width - |%d|", img->img.height, img->img.width);
//	exit(1);
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

void	ft_move_trace(t_game *img, char (*world_map)[img->map_width],
				   int i, int j)
{
	int flag;
	int k;

	flag = 0;
	k = 0;
	printf("i: %d j: %d", i, j);
	while (k < img->map_height * img->map_width)
	{
		if (world_map[i + 1][j] == '1' && !(flag & UP))
		{
			flag |= DOWN;
			i++;
		}
		else if (world_map[i][j - 1] == '1')
		{
			flag = 0;
			j--;
		}
		else if (world_map[i - 1][j] == '1' && world_map[i - 1][j] && !(flag & DOWN))
		{
			flag |= UP;
			i--;
		}
		else if (world_map[i][j + 1] == '1' && world_map[i][j + 1])
		{
			flag = 0;
			j++;
		}
		else
		{
			printf("Error: not a valid map");
			exit(1);
		}
		k++;
	}
}

void	ft_check_valid_map(t_game *img, t_list **list_head)
{
	int i = 0;
	int j = 0;

	t_list *list;
	printf("helloooooooooooooooooooooooooooooooooooooooo\n");

	i = 0;
	j = 0;
	list = *list_head;
	while (i < img->map_height && list)
	{
		printf("hzh3_map: |");
		while (j < img->map_width)
		{
			printf("%c", img->world_map[i][j]);
			j++;
		}
		j = 0;
		i++;
		printf("|\n");
		list = list->next;
	}


	i = 0;
	j = 0;
	int flag;

	flag = 0;
//	exit(1);
//	printf("\thello algorithm\t\n");
//	while (i < img->map_height)
//	{
//		while (j < img->map_width)
//		{
////			printf("-----------|%c|", world_map[i][j]);
//			if(world_map[i][j] == '1' || world_map[i][j] == '2'
//			|| world_map[i][j] == '0' || world_map[i][j] == ' ')
//			{
//				if (!world_map[i][j + 1] && world_map[i][j] == '1')
//				{
//					printf("\tits broken\t\n");
//					ft_move_trace(img, world_map, i, j);
//				}
//				j++;
//			}
//		}
//		j = 0;
//		i++;
//	}
//	printf("|%c|", world_map[0][0]);

	i = 0;
	j = 0;
	list = *list_head;

	while (i < img->map_height && list)
	{
		printf("lols_map: |");
		while (j < img->map_width)
		{
			printf("%c", (img->world_map)[i][j]);
			j++;
		}
		j = 0;
		i++;
		printf("|\n");
		list = list->next;
	}

}

void	ft_fill_map(t_game *img, t_list **list_head)
{
	t_list	*list;
//	char	world_map[(int)img->map_height][(int)img->map_width];
//	char	**world_map;
	int 	i;
	int 	j;

	i = 0;
	j = 0;
	list = *list_head;

	img->world_map = (char **)ft_calloc(img->map_height, sizeof (char *));
	while (i < img->map_height)
		img->world_map[i++] = (char *)ft_calloc(img->map_width, sizeof (char));
	//	printf("|%c|\n", world_map[i][j]);
	while (i++ < img->map_height)
	{
		printf("list_map: |");
		while (j++ < img->map_width)
			printf("x");
		j = 0;
		printf("|\n");
	}
	while (list) //print list по столбикам
	{
		printf("list_map: |%s|\n", (char *)list->content);
		list = list->next;
	}
	list = *list_head;
	i = 0;
	j = 0;
	int k;

	k = 0;
	while (i < img->map_height && list)
	{
		printf("main_map: |");
		k = ft_strlen(list->content);
		ft_strlcpy(img->world_map[i], list->content, k + 1);
		j = 0;
		i++;
		list = list->next;
		printf("|\n");
	}

	i = 0;
	j = 0;
	list = *list_head;
	while (i < img->map_height && list)
	{
		printf("hzh2_map: |");
		while (j < img->map_width)
		{
			printf("%c", img->world_map[i][j]);
			j++;
		}
		j = 0;
		i++;
		printf("|\n");
		list = list->next;
	}
	ft_check_valid_map(img, list_head);
}

void	ft_parse_tail(t_game *img, char **line, const int *fd)
{
	int i;
	int j;
	t_list	*list_head = NULL;
	t_list	*list;

	j = 0;
	while ((i = get_next_line(*fd, line)) > 0)
	{
		if (!list_head && ft_isascii_content(*line))
		{
			list_head = ft_lstnew(*line);
			continue;
		}
		list = ft_lstnew(*line);
		if(ft_isascii_content(list->content))
		{
			ft_lstadd_back(&list_head, list);
			printf("i = %d |%s|\n", i, *line);
			j++;
		}
		else
			free(list);
	}
	printf("i = %d |%s|\n", i, *line);
	list = ft_lstnew(*line);
	ft_lstadd_back(&list_head, list);

//	free(list);
	list = list_head;
	printf("ALLALDLFLLFLALFL 1: |%d|\n", img->map_width);
	while (list) //print list
	{
		printf("list: |%s|\n", (char *)list->content);
		list = list->next;
	}
	img->map_height = ft_lstsize(list_head);

	list = list_head;
	printf("ALLALDLFLLFLALFL 2: |%d|\n", img->map_width);
	while (list) //print list
	{
		if (img->map_width < ft_strlen(list->content))
			img->map_width = (int)ft_strlen(list->content);
		list = list->next;
	}
	printf("size height: |%d|\n", img->map_height);
	printf("size width: |%d|\n", img->map_width);
	list = list_head;
//	printf("content: |%s| ascii?: %d\n", list->content, ft_isascii_content(list->content));
	ft_fill_map(img, &list_head);
}

void	ft_parser(int argc, char **argv, t_game *img)
{
	int i;
	int j;
	int fd;
	char *line;

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
	if (argc == 2)
	{
		while ((i = get_next_line(fd, &line)) && j <= 7)
		{
			ft_parse_head(&line, img);
			if (*line != '\0')
				j++;
			free(line);
			ft_check_flag(img);
		}
		ft_parse_tail(img, &line, &fd);
	}
	else if (argc == 3)
	{

	}
	else
		printf("Error: no valid arguments\n");
	printf("Result: %s", strerror(errno));
}
