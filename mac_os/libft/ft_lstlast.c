/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 20:30:04 by brice             #+#    #+#             */
/*   Updated: 2020/11/11 07:16:20 by brice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	size_t i;

	i = 0;
	if (!lst)
		return (lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
}