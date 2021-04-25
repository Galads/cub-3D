/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 18:38:56 by brice             #+#    #+#             */
/*   Updated: 2021/04/25 18:41:49 by brice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"

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

void	ft_parse_tail(t_game *img, char **line, const int *fd)
{
	t_list *list_head = NULL;
	t_list *list = NULL;

	while (img->i >= 0)
	{
		img->i = get_next_line(*fd, line);
		ft_check_line(line, &list_head, &list, img);
		if (img->i == 0)
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

int	ft_parser_open(t_game *img, char **argv)
{
	int fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_print_error(img, "fd < 0", 1);
	}
	ft_init_parser(img);
	if (!argv[1])
	{
		printf("Error: not a argument\n");
		exit(1);
	}
	return (fd);
}

void	ft_parser(int argc, char **argv, t_game *img)
{
	int		i;
	int		fd;
	char	*line;

	i = 1;
	(void)argc;
	fd = ft_parser_open(img, argv);
	while ((i > 0) && img->j_ps < 8)
	{
		i = get_next_line(fd, &line);
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
