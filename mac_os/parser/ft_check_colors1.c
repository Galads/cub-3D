/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_colors1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 16:26:44 by brice             #+#    #+#             */
/*   Updated: 2021/04/25 16:27:06 by brice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_check_colors1(char **result, int *i, int *j)
{
	if (result[(*i)][(*j)] == ' '
		|| result[(*i)][(*j)] == 'F' || result[(*i)][(*j)] == 'C')
		(*j)++;
	else if (!ft_isdigit(result[(*i)][(*j)])
			 && result[(*i)][(*j)] != '\0' && result[(*i)][(*j)] != ' ' )
	{
		printf("Error: not a valid strings\n");
		exit(13);
	}
	else
	{
		while (ft_isdigit(result[(*i)][(*j)]))
			(*j)++;
	}
}
