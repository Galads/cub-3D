/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 09:30:08 by brice             #+#    #+#             */
/*   Updated: 2021/04/25 09:33:46 by brice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ft_create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	ft_parse_t_a_s(const char **result, t_game *img)
{
	if (!ft_strncmp(*result, "R", INT_MAX) && !(img->flag_control & RES))
		img->flag_parser |= RES;
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

void	ft_check_if(t_game *img, char **result)
{
	if (img->flag_parser & RES && result[1] && result[2] && !result[3])
	{
		img->img.height = ft_atoi(result[1]);
		img->img.width = ft_atoi(result[2]);
		if (img->img.width < 0)
		{
			img->img.width = WIDTH;
			exit(3);
		}
		if (img->img.height < 0)
		{
			img->img.height = HEIGHT;
			exit(3);
		}
		img->j_ps++;
	}
	if (img->flag_parser & S && result[1] && !result[2])
	{
		img->sprite.relative_path = ft_strdup((char *)result[1]);
		img->j_ps++;
	}
	if (img->flag_parser & NO && result[1] && !result[2])
	{
		img->texture_n.relative_path = ft_strdup((char *)result[1]);
		img->j_ps++;
	}
	if (img->flag_parser & SO && result[1] && !result[2])
	{
		img->texture_s.relative_path = ft_strdup((char *)result[1]);
		img->j_ps++;
	}
}

void	ft_check_if_last(t_game *img, char **result)
{
	if (img->flag_parser & WE && result[1] && !result[2])
	{
		img->texture_w.relative_path = ft_strdup((char *)result[1]);
		img->j_ps++;
	}
	if (img->flag_parser & EA && result[1] && !result[2])
	{
		img->texture_e.relative_path = ft_strdup((char *)result[1]);
		img->j_ps++;
	}
	if (img->flag_parser & F && *result[2] ==',' && *result[4] == ','
		&& ft_isaint(ft_atoi(&*(result)[1]))
		&& ft_isaint(ft_atoi(&(*result)[3]))
		&& ft_isaint(ft_atoi(&*(result)[5])))
	{
		img->rc.col_f = ft_create_trgb(0, ft_atoi(result[1]),
				ft_atoi(result[3]), ft_atoi(result[5]));
		img->j_ps++;
	}
}

void	ft_parse_str(const char **result, t_game *img)
{
	ft_check_if(img, (char **) result);
	ft_check_if_last(img, (char **) result);
	if (img->flag_parser & C && ft_isaint(ft_atoi(&*(result)[1]))
		&& ft_isaint(ft_atoi(&(*result)[3]))
		&& ft_isaint(ft_atoi(&*(result)[5])))
	{
		img->rc.col_c = ft_create_trgb(0,
				ft_atoi(result[1]), ft_atoi(result[3]), ft_atoi(result[5]));
		img->j_ps++;
	}
	else
		printf("Warning: maybe map not a valid\n");
}
