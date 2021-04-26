/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_handlers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 09:34:18 by brice             #+#    #+#             */
/*   Updated: 2021/04/25 17:01:30 by brice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

void	ft_fill_flag(t_game *img)
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
		ft_print_error(img, "many count headers elements\n", 7);
}

void	ft_check_line_first(char **line, t_list **list_head,
			int *k, t_game *img)
{
	if ((*line)[(*k)] && (*line)[(*k)] != '1')
	{
		free(*line);
		ft_print_error(img, "invalid map\n", 45);
	}
	if ((*line)[(*k)] == '\0' && *list_head && img->i != 0)
	{
		free(*line);
		ft_print_error(img, "invalid map\n", 45);
	}
	while ((*line)[(*k)])
	{
		if (ft_memchr("1 ", (*line)[(*k)], 2))
		{
			if (!*list_head)
			{
				*list_head = ft_lstnew(*line);
				(img->flag_p) = 0;
			}
		}
		(*k)++;
	}
}

void	ft_check_line(char **line, t_list **list_head,
			t_list **list, t_game *img)
{
	int	k;
	int	k5;

	img->flag_p = 1;
	k = ft_valid_line(line);
	k5 = k;
	ft_check_line_first(line, list_head, &k, img);
	if (img->flag_p == 1 && (*line)[k5])
	{
		*list = ft_lstnew(*line);
		ft_lstadd_back(list_head, *list);
	}
	else if (!(*line)[k5])
		free(*line);
}
