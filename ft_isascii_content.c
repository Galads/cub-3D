//
// Created by galads on 20.04.2021.
//

#include "libft/libft.h"
int	ft_isascii_content(void *c)
{
	if (*(char *)c == '\0')
		return (0);
	return (*(char *)c >= 0 && *(char *)c <= 127);
}
