# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brice <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/02 10:41:41 by brice             #+#    #+#              #
#    Updated: 2020/11/13 02:42:04 by brice            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= ./ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
			  ft_memchr.c ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c \
			  ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c \
			  ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
			  ft_toupper.c ft_tolower.c ft_calloc.c ft_strdup.c ft_substr.c \
			  ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
			  ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

OBJS		= ${SRCS:.c=.o}

INCLUDES	= ./libft.h

CFLAGS		= -Wall -Wextra -Werror

GCC			= gcc

NAME		= libft.a

SRC_OBJ		= ./ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
			  ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
			  ft_lstmap.c

BONUS		= ${SRC_OBJ:.c=.o}

all:		${NAME}

$(NAME):
		${GCC} -c -I ${INCLUDES} ${CFLAGS} ${SRCS}
		ar rc ${NAME} ${OBJS}
		ranlib ${NAME}

bonus:  $(OBJS) $(BONUS)
	 	ar rc $(NAME) $(BONUS) $(OBJS)

clean:
		rm -f ${OBJS} 
		rm -f ${BONUS}

fclean:	clean
		rm -f ${NAME}

re:		fclean  all

.PHONY: all clean fclean re $(NAME) bonus
