/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 22:35:37 by brice             #+#    #+#             */
/*   Updated: 2020/11/25 12:41:48 by brice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	int	ft_strcopy(char **save, char **line)
{
	char	*clear;

	clear = *line;
	if (!(*line = ft_strjoin(*line, *save)))
	{
		free(clear);
		return (-1);
	}
	free(clear);
	return (1);
}

static	int	if_save_true(char **line, char **p, char **clear, char **save)
{
	if ((*p = ft_strchr(*save, '\n')))
	{
		**p = '\0';
		if ((ft_strcopy(save, line)) < 0)
			return (-1);
		*clear = *save;
		if (!(*save = ft_strdup(*p + 1)))
		{
			free(*clear);
			return (-1);
		}
		free(*clear);
		return (-2);
	}
	else
	{
		if ((ft_strcopy(save, line)) < 0)
			return (-1);
		free(*save);
		*save = NULL;
		return (1);
	}
}

static	int	get_line_while(char **p, int *fd, char **line, char **save)
{
	char	*buf;
	int		rd;

	if (!(buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while (!*p && (rd = read(*fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[rd] = '\0';
		if ((*p = ft_strchr(buf, '\n')))
		{
			**p = '\0';
			if (!(*save = ft_strdup(*p + 1)))
			{
				free(buf);
				return (-1);
			}
		}
		if ((ft_strcopy(&buf, line)) < 0)
		{
			free(buf);
			return (-1);
		}
	}
	free(buf);
	return (rd);
}

int			get_next_line(int fd, char **line)
{
	static char	*save;
	char		*clear;
	char		*p;
	int			rd;
	int			flag;

	if (fd < 0 || BUFFER_SIZE < 1 || !line)
		return (-1);
	if (!(*line = ft_strdup("")))
		return (-1);
	if (save)
	{
		flag = if_save_true(line, &p, &clear, &save);
		if (flag == -1)
			return (-1);
		else if (flag == -2)
			return (1);
	}
	else
		p = NULL;
	rd = get_line_while(&p, &fd, line, &save);
	if (save)
		return (1);
	free(save);
	return ((rd < 0) ? -1 : 0);
}
