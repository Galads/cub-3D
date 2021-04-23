cmake_minimum_required(VERSION 3.19)
project(mac_os C)

set(CMAKE_C_STANDARD 99)

include_directories(/usr/local/include)
include_directories(
        /Users/brice/Desktop/cub3d/Cub3D/linux/textures/
        /Users/brice/Desktop/cub3d/Cub3D/linux/sprites/
)

add_executable(mac_os
        ft_parser.c
        main3D.c
#        minilibx_mms_20200219/mlx.h
        get_next_line/get_next_line.h
        get_next_line/get_next_line.c
        get_next_line/get_next_line_utils.c
        libft/ft_split.c
        libft/ft_strnstr.c
        libft/ft_strncmp.c
        libft/ft_strlen.c
        libft/ft_atoi.c
        libft/ft_isdigit.c
        libft/ft_calloc.c
        libft/ft_strlcpy
#        libft/ft_isaint.c
        libft/ft_lstadd_back.c
        libft/ft_lstnew.c
        libft/ft_lstlast.c
        libft/ft_lstsize.c
        libft/ft_isascii.c
        ./ft_isascii_content.c
        ./ft_isaint.c
#        graphics
        reycasting/ft_reycasting.h
        reycasting/ft_print_texture.c
        reycasting/ft_rc_s_first.c
        reycasting/ft_base_rc_value.c
        reycasting/ft_calc_step_init_side.c
        reycasting/ft_rc_hit.c
        reycasting/ft_vertical_line.c
        libft/ft_lstclear.c

#        minilibx_mms_20200219/mlx_rgb.c
#        minilibx_mms_20200219/mlx_png.c
#        minilibx_mms_20200219/mlx_string_put.c
#        minilibx_mms_20200219/mlx_xpm.c
#        minilibx_opengl_20191021/mlx.h
#        minilibx_opengl_20191021/mlx_xpm.c
#        minilibx_opengl_20191021/mlx_png.c
#        minilibx_opengl_20191021/mlx_rgb.c
#        minilibx_opengl_20191021/mlx_int.h
#        minilibx_opengl_20191021/mlx_int_str_to_wordtab.c
#        minilibx_opengl_20191021/mlx_png.h
#        minilibx_opengl_20191021/mlx_new_window.h
#        minilibx_opengl_20191021/mlx_opengl.h
#        minilibx_opengl_20191021/mlx_shaders.c
        screenshot.bmp
        reycasting/ft_control_plr.c reycasting/ft_move_player.c reycasting/ft_init_val.c reycasting/ft_open_tex_spr.c reycasting/ft_key_hook_handle.c reycasting/ft_calc_and_print_sprite.c ft_free_memory.c ft_screen_shot.c ft_valid_line.c)
#mac_os target
target_link_libraries(mac_os "-framework OpenGL")
target_link_libraries(mac_os "-framework AppKit")
target_link_libraries(mac_os /usr/local/lib/libmlx.a)

#linux target
#target_link_libraries(mac_os "-Lminilibx-linux/ -lmlx -L/usr/lib")
#target_link_libraries(mac_os "-Lminilibx-linux -Imlx_linux -O3")
#target_link_libraries(mac_os "-lXext -lX11 -lbsd -lm")
#target_link_libraries(mac_os /usr/lib/libmlx.a)