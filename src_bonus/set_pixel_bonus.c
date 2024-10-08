/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:54:33 by ajovanov          #+#    #+#             */
/*   Updated: 2024/09/24 10:54:34 by ajovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	set_pixel_variables(t_set_pixel *pixel, int color, int x, int y)
{
	pixel->color = color;
	pixel->x = x;
	pixel->y = y;
}

void	set_pixel(char *img_data, t_set_pixel pix, int size_line, int bpp)
{
	int	pixel;

	pixel = (pix.y * size_line) + (pix.x * (bpp / 8));
	img_data[pixel + 0] = (pix.color & 0xFF);
	img_data[pixel + 1] = (pix.color >> 8) & 0xFF;
	img_data[pixel + 2] = (pix.color >> 16) & 0xFF;
	img_data[pixel + 3] = (pix.color >> 24);
}

void	set_the_pixel_looping(t_cub3d *game, t_img_rendering *img)
{
	t_set_pixel	pixel;
	int			i;
	int			j;

	i = img->start_x;
	while (i < img->end_x)
	{
		j = img->start_y;
		while (j < img->end_y)
		{
			set_pixel_variables(&pixel, img->color, i, j);
			set_pixel(game->img.img_data, pixel, img->size_line, img->bpp);
			j++;
		}
		i++;
	}
}
