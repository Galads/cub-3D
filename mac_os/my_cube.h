/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cube.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 12:33:32 by brice             #+#    #+#             */
/*   Updated: 2021/04/21 12:47:43 by brice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_CUBE_H
# define MY_CUBE_H
# define RGB_1			0x00FF0000
# define M_F			0x001
# define M_B			0x002
# define M_R			0x010
# define M_L			0x020
# define R_R			0x100
# define R_L			0x200
# define RES			0x0001
# define NO				0x0002
# define SO				0x0010
# define WE				0x0020
# define EA				0x0100
# define S				0x0200
# define F				0x1000
# define C				0x2000

# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include "mlx.h"
# include "math.h"
# include "stdlib.h"
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"

typedef struct s_vector
{
	double		v_x;
	double		v_y;
}				t_vector;

typedef struct s_player
{
	double		pl_x;
	double		pl_y;
}				t_player;

typedef struct s_pos
{
	double		pos_x;
	double		pos_y;
	double		plane_x;
	double		plane_y;
}				t_pos;

typedef struct s_sprite
{
	double			x;
	double			y;
	void			*img;
	char			*addr;
	double			*sprite_distance;
	double			*z_buffer;
	int				*sprite_order;
	int				line_length;
	int				endian;
	int				width;
	int				height;
	int				bits_per_pixel;
	char			*relative_path;
	int				stripe;
	int				sprite_width;
	int				sprite_height;
	int				draw_start_y;
	int				draw_end_y;
	int				sprite_screen_x;
	double			sprite_x;
	double			sprite_y;
	double			inv_det;
	double			transform_x;
	double			transform_y;
	long long int	count;
}					t_sprite;

typedef struct s_data
{
	void	*mlx;
	void	*img;
	char	*addr;
	void	*win;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
	char	*relative_path;
}			t_data;

typedef struct s_rey
{
	double	pos_x;
	double	pos_y;
	int		x;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		color;
	int		tex_x;
	int		tex_y;
	int		col_c;
	int		col_f;
}			t_rey;

typedef struct s_game
{
	t_data			texture_n;
	t_data			texture_s;
	t_data			texture_w;
	t_data			texture_e;
	t_sprite		sprite;
	t_sprite		*sp;
	t_data			img;
	t_vector		vector;
	t_pos			pos;
	t_rey			rc;
	unsigned int	flags;
	unsigned int	flag_parser;
	unsigned int	flag_control;
	long long int	map_width;
	long long int	map_height;
	char			**world_map;
	int				flag_screen;

}					t_game;

int		ft_isaint(int c);
int		ft_isascii_content(void *c);
void	ft_parser(int argc, char **argv, t_game *img);
void	ft_free_memory(t_game *img);
void	ft_screen_shot(t_game *img);
char	*ft_valid_line(char **line);
#endif
