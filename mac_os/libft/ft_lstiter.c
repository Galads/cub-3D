/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 22:55:12 by brice             #+#    #+#             */
/*   Updated: 2020/11/09 23:02:01 by brice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list *l;

	l = 0;
	if (!lst || !f)
		return ;
	while (lst)
	{
		l = lst->next;
		f(lst->content);
		lst = l;
	}
}