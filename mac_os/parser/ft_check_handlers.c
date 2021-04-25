/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_handlers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 09:34:18 by brice             #+#    #+#             */
/*   Updated: 2021/04/25 09:38:44 by brice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_check_colors(char **result)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (result[i])
	{
		while (result[i][j])
		{
			if (result[i][j] == ' ' || result[i][j] == 'F'
				|| result[i][j] == 'C')
				j++;
			else if (!ft_isdigit(result[i][j]) && result[i][j] != '\0' && result[i][j] != ' ' )
			{
				printf("Error: not a valid strings\n");
				exit(13);
			}
			else
			{
				while (ft_isdigit(result[i][j]))
					j++;
			}
		}
		j = 0;
		i++;
	}
}

void	ft_handler_f_c(int *col, char **result)
{
	int	i;
	int	j;
	int	k;
	int	rgb[3];

	i = 0;
	j = 1;
	k = 0;
	ft_check_colors(result);
	while (result[i])
	{
		while (result[i][j])
		{
			if (result[i][j] == ' ' || result[i][j] == 'F'
					|| result[i][j] == 'C')
				j++;
			else if (ft_isdigit(result[i][j]))
			{
				rgb[k++] = ft_atoi(&result[i][j]);
				break ;
			}
			else
			{
				printf("Error: not a valid string header\n");
				exit(1);
			}
		}
		j = 0;
		i++;
	}
	*col = ft_create_trgb(0, rgb[0], rgb[1], rgb[2]);
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
	{
		printf("Error: many count headers elements\n");
		exit(1);
	}
}

void	ft_check_line_first(char **line, t_list **list_head, int *k, t_game *img)
{
	if ((*line)[(*k)] && (*line)[(*k)] != '1')
	{
		free(*line);
		printf("Error: invalid map\n");
		exit(45);
	}
	if ((*line)[(*k)] == '\0' && *list_head && img->i != 0)
	{
		free(*line);
		printf("Error: invalid map\n");
		exit(46);
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

void	ft_check_line(char **line, t_list **list_head, t_list **list, t_game *img)
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