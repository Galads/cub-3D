/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_screen_shot.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 03:11:23 by brice             #+#    #+#             */
/*   Updated: 2021/04/23 03:15:44 by brice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reycasting/ft_reycasting.h"

unsigned int	my_mlx_pixel_put2(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	ft_read_inf_head(t_game *img, unsigned char *information_header)
{
	information_header[0] = 40;
	information_header[4] = img->img.width;
	information_header[5] = img->img.width >> 8;
	information_header[6] = img->img.width >> 16;
	information_header[7] = img->img.width >> 24;
	information_header[8] = img->img.height;
	information_header[9] = img->img.height >> 8;
	information_header[10] = img->img.height >> 16;
	information_header[11] = img->img.height >> 24;
	information_header[12] = 1;
	information_header[14] = 24;
}

void	ft_write_header(t_game *img, int file_size, int fd)
{
	unsigned char	file_header[14];
	unsigned char	information_header[40];
	int				i;

	i = 0;
	while (i < 14)
		file_header[i++] = 0;
	i = 0;
	while (i < 40)
		information_header[i++] = 0;
	file_header[0] = 'B';
	file_header[1] = 'M';
	file_header[2] = file_size;
	file_header[3] = file_size >> 8;
	file_header[4] = file_size >> 16;
	file_header[5] = file_size >> 24;
	file_header[10] = 40 + 14;
	ft_read_inf_head(img, information_header);
	write(fd, file_header, 14);
	write(fd, information_header, 40);
}

void	ft_write_body(t_game *img, unsigned char *color, int fd,
				   int padd_amount)
{
	int				y;
	int				x;
	unsigned int	bmp_pad[3];

	bmp_pad[0] = 0;
	bmp_pad[1] = 0;
	bmp_pad[2] = 0;
	y = img->img.height;
	while (y > 0)
	{
		x = img->img.width;
		while (x > 0)
		{
			color[0] = (my_mlx_pixel_put2(&img->img, x, y) & 0x0000FF);
			color[1] = ((my_mlx_pixel_put2(&img->img, x, y) >> 8) & 0x0000FF);
			color[2] = ((my_mlx_pixel_put2(&img->img, x, y) >> 16) & 0x0000FF);
			write(fd, color, 3);
			x--;
		}
		write(fd, bmp_pad, padd_amount);
		y--;
	}
}

void	ft_screen_shot(t_game *img)
{
	int				fd;
	int				padd_amount;
	int				file_size;
	unsigned char	color[3];

	padd_amount = 0;
	fd = open("screenshot.bmp", O_CREAT | O_WRONLY, S_IREAD | S_IWRITE);
	if (!fd)
		printf("Error: %s", strerror(errno));
	else
	{
		file_size = 40 + 14 + img->img.width * img->img.height
			* 3 + padd_amount * img->map_height;
		padd_amount = (4 - (img->img.width * 3) % 4) % 4;
		ft_write_header(img, file_size, fd);
		ft_write_body(img, color, fd, padd_amount);
	}
	close(fd);
}
