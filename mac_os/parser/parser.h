/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 17:26:31 by brice             #+#    #+#             */
/*   Updated: 2021/04/25 17:28:20 by brice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "../reycasting/ft_reycasting.h"
void	ft_parse_t_a_s(const char **result, t_game *img);
void	ft_parse_str(const char **result, t_game *img);
void	ft_check_if(t_game *img, char **result);
void	ft_check_if_last(t_game *img, char **result);
int		ft_create_trgb(int t, int r, int g, int b);
void	ft_handler_f_c(int *col, char **result, t_game *img);
void	ft_fill_flag(t_game *img);
void	ft_check_line(char **line, t_list **list_head,
			t_list **list, t_game *img);
int		ft_parse_head_if_int(t_game *img, char **result, char **line, int *i);
void	ft_free_split(char **line);
int		ft_check_str_num(char **result);
void	ft_parse_head(char **line, t_game *img);
void	ft_init_parser(t_game *img);
void	ft_check_line_first(char **line, t_list **list_head,
			int *k, t_game *img);
void	ft_check_if_f(t_game *img, char **result);
void	ft_check_colors1(char **result, int *i, int *j);
int		ft_handler_f_c1(char **result, t_game *img, int *rgb);
void	ft_handler_f_c(int *col, char **result, t_game *img);
void	ft_parse_head_if_int_1(char **result, t_game *img);
int		ft_check_addr_mem(char *result, char c);

#endif
