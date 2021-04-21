cmake_minimum_required(VERSION 3.19)
project(ft_parser C)

set(CMAKE_C_STANDARD 99)

add_executable(ft_parser
        ft_parser.c
        get_next_line/get_next_line.h
        get_next_line/get_next_line.c
        get_next_line/get_next_line_utils.c
        libft/ft_split.c
        libft/ft_strnstr.c
        libft/ft_strncmp.c
        libft/ft_strlen.c
        libft/ft_atoi.c
        libft/ft_isdigit.c
        libft/ft_isaint.c
        libft/ft_lstadd_back.c
        libft/ft_lstnew.c
        libft/ft_lstlast.c
        libft/ft_lstsize.c
        libft/ft_isascii.c
        libft/ft_isaint.c
        ft_isascii_content.c)
include_directories(get_next_line)