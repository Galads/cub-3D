#include <string.h>
#include <errno.h>
#include "reycasting/ft_reycasting.h"

void	my_mlx_img_put(t_data *win, int x, int y, int color)
{
	char	*dst;

	dst = win->addr + (y * win->line_length + x * (win->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
unsigned int	my_mlx_pixel_put2(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return *(unsigned int *)dst;
}


void	ft_screen_shot(t_game *img)
{
	int fd;
	char *buf = "123";

	fd = open("screenshot.bmp", O_CREAT | O_WRONLY, S_IREAD | S_IWRITE);
	if (!fd)
		printf("Error: %s", strerror(errno));
	else
	{

		int padd_amount;
		unsigned int bmp_pad[3] = {0, 0, 0};
		int	file_header_size = 14;
		int	information_header_s = 40;
		int	file_size = information_header_s + file_header_size  + img->img.width
				* img->img.height * 3 + padd_amount * img->map_height;
		padd_amount = (4 - (img->img.width * 3) % 4) % 4;

		unsigned char file_header[file_header_size];

		file_header[0] = 'B';
		file_header[1] = 'M';
		file_header[2] = file_size;
		file_header[3] = file_size >> 8;
		file_header[4] = file_size >> 16;
		file_header[5] = file_size >> 24;
		//not use reserv1
		file_header[6] = 0;
		file_header[7] = 0;
		//not use reserv2
		file_header[8] = 0;
		file_header[9] = 0;
		// pixels data_offset
		file_header[10] = information_header_s + file_header_size;
		file_header[11] = 0;
		file_header[12] = 0;
		file_header[13] = 0;

		unsigned char information_header[information_header_s];
		//header size
		information_header[0] = information_header_s;
		information_header[1] = 0;
		information_header[2] = 0;
		information_header[3] = 0;
		//img width
		information_header[4] = img->img.width;
		information_header[5] = img->img.width >> 8;
		information_header[6] = img->img.width >> 16;
		information_header[7] = img->img.width >> 24;
		//img height
		information_header[8] = img->img.height;
		information_header[9] = img->img.height >> 8;
		information_header[10] = img->img.height >> 16;
		information_header[11] = img->img.height >> 24;
		//planes
		information_header[12] = 1;
		information_header[13] = 0;
		//bpp
		information_header[14] = 24;
		information_header[15] = 0;
		//compression
		information_header[16] = 0;
		information_header[17] = 0;
		information_header[18] = 0;
		information_header[19] = 0;
		//img size compression
		information_header[20] = 0;
		information_header[21] = 0;
		information_header[22] = 0;
		information_header[23] = 0;
		//x pixel per meter
		information_header[24] = 0;
		information_header[25] = 0;
		information_header[26] = 0;
		information_header[27] = 0;
		//y pixel per meter
		information_header[28] = 0;
		information_header[29] = 0;
		information_header[30] = 0;
		information_header[31] = 0;
		//color table
		information_header[32] = 0;
		information_header[33] = 0;
		information_header[34] = 0;
		information_header[35] = 0;
		//important color
		information_header[36] = 0;
		information_header[37] = 0;
		information_header[38] = 0;
		information_header[39] = 0;

		write(fd, file_header, file_header_size);
		write(fd, information_header, information_header_s);

		for(int y = img->img.height; y > 0; y--)
		{
			for(int x = img->img.width; x > 0; x--)
			{
				unsigned char r = (my_mlx_pixel_put2(&img->img, x, y) & 0x0000FF);
				unsigned char g = ((my_mlx_pixel_put2(&img->img, x, y) >> 8) & 0x0000FF);
				unsigned char b = ((my_mlx_pixel_put2(&img->img, x, y) >> 16) & 0x0000FF);

				unsigned char color[3] = {r, g, b};
				write(fd, color, 3);
			}
			write(fd, bmp_pad, padd_amount);
		}
	}
	close(fd);
}