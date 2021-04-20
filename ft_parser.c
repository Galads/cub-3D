#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <error.h>
#include "errno.h"
#include "get_next_line/get_next_line.h"
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
//	printf("height - |%d|, width - |%d|\n", img->img.height, img->img.width);
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
		ft_parse_t_a_s(result, img);
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
}

void ft_fill_map(t_game *img, t_list **list_head)
{
	t_list	*list;
	char	world_map[(int)img->map_width][(int)img->map_height];
	int 	i;
	int 	j;

	i = 0;
	j = 0;
	list = *list_head;

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
	while (i++ < img->map_height && list)
	{
		printf("main_map: |");
		while (j < img->map_width)
		{
			if ((((char *)list->content)[j]))
				world_map [i][j] = (((char *)list->content)[j]);
			else
				world_map [i][j] = ' ';
			printf("%c", world_map[i][j]);
			j++;
		}
		j = 0;
		list = list->next;
		printf("|\n");
	}
//	ft_check_valid(img, )
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
			list_head = ft_lstnew(*line);
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
	while (list) //print list
	{
		printf("list: |%s|\n", (char *)list->content);
		list = list->next;
	}
//	exit(1);
	img->map_height = ft_lstsize(list_head);

	list = list_head;
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

void	ft_parser(int argc, char **argv)
{
	t_game img;
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
//	printf("fd %d\n", fd);
	ft_init_parser(&img);

	if (!argv[1])
		printf("Error: no map\n");
	if (argc == 2)
	{
		printf("%s\n", argv[1]);
		while ((i = get_next_line(fd, &line)) && j <= 7)
		{
			ft_parse_head(&line, &img);
			printf("|%s|\n", line);
			printf("%d\n", i);
			if (*line != '\0')
				j++;
			free(line);
			ft_check_flag(&img);
		}
//		printf("after while |%s|\n", line);
		ft_parse_tail(&img, &line, &fd);
//		printf("after while |%s|\n", line);
//		printf("%d\n", i);
//		free(line);
//		printf("F: %x, C: %x\n", img.rc.col_f, img.rc.col_c);
//		printf("color %d\n", ft_atoi("255"));
	}
	else if (argc == 3)
	{

	}
	else
		printf("Error: no valid arguments\n");
	printf("Result: %s", strerror(errno));
}
int main(int argc, char **argv)
{
	char *line;

	line = ft_strnstr(argv[1], ".cub", INT_MAX);
	if (line)
		ft_parser(argc, argv);
	else
		printf("Error: no find file with expansion \".cub\"\n");
	return 0;
}
