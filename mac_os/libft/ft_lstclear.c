/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 21:53:49 by brice             #+#    #+#             */
/*   Updated: 2020/11/10 02:26:49 by brice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*j;

	j = 0;
	if (!*lst || !del)
		return ;
	while (*lst)
	{
		j = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = j;
	}
	lst = NULL;
}
