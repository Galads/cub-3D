CC			= gcc

NAME		= cub3D

INCLUDES	= ./libft/

MLX			= ./minilibx_opengl_20191021/

# MLX			= ./minilibx-linux/

PARS_DIR	= ./parser/

GNL_DIR		= ./get_next_line/

#MEM_DIR		= ./destroy_memory/

#HERRORS_DIR	= ./handler_errors/

#CUBE_DIR	= ./ft_cube/

#GAME_DIR	= ./ft_cube/game_control/

REYCAST_DIR	= ./reycasting/

SRCS		= main3D.c	 $(GNL_DIR)get_next_line.c $(GNL_DIR)get_next_line_utils.c\
				          $(PARS_DIR)ft_check.c  $(PARS_DIR)ft_parse.c $(PARS_DIR)ft_parse_inter.c\
				          $(PARS_DIR)ft_check_handlers.c\
				          $(REYCAST_DIR)ft_base_rc_value.c\
				          $(REYCAST_DIR)ft_calc_and_print_sprite.c\
				          $(REYCAST_DIR)ft_calc_step_init_side.c\
				          $(REYCAST_DIR)ft_control_plr.c\
				          $(REYCAST_DIR)ft_init_val.c\
				          $(REYCAST_DIR)ft_key_hook_handle.c\
				          $(REYCAST_DIR)ft_move_player.c\
				          $(REYCAST_DIR)ft_open_tex_spr.c\
				          $(REYCAST_DIR)ft_print_texture.c\
				          $(REYCAST_DIR)ft_rc_hit.c\
				          $(REYCAST_DIR)ft_rc_s_first.c\
				          $(REYCAST_DIR)ft_vertical_line.c\
				          libft/ft_lstadd_back.c\
				    	  libft/ft_lstnew.c libft/ft_lstclear.c libft/ft_lstlast.c libft/ft_lstsize.c\
				          ft_free_memory.c ft_isaint.c ft_parser.c ft_screen_shot.c ft_valid_line.c map_parser.c\
				          map_parser_utils.c\


CFLAGS		= -Wall -Wextra -Werror

OBJS		= $(SRCS:.c=.o)

LIBS		= -L. -lmlx -framework OpenGL -framework AppKit -lm -Llibft -lft

# LIBS = -Lminilibx-linux/ -lmlx -L/usr/lib -lXext -lX11 -lm -lbsd -Llibft -lft # for linux

all:	$(NAME)

%.o:	%.c
		$(CC) $(CFLAGS) -I$(INCLUDES) -I$(MLX) -c $< -o $@

$(NAME):	$(OBJS)
		make -C libft/
		make -C $(MLX)
		$(CC) -o $(NAME) $(CFLAGS) -I$(INCLUDES) -O2 -I$(MLX) $(OBJS) $(LIBS)

clean:
		make -C libft/ clean
		make -C $(MLX) clean
		rm -rf $(OBJS)

fclean:	clean
		make -C libft/ fclean
		# @make -C $(MLX) fclean
		rm -rf $(NAME)

re:		fclean all

t:
	./cub3D 
