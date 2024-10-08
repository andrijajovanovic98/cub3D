/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rending.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:52:19 by ajovanov          #+#    #+#             */
/*   Updated: 2024/09/24 10:52:22 by ajovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	rend_minimap_looping(
			t_cub3d *game, t_img_rendering *img, t_minimap *var, int *color)
{
	double	dist;

	var->x_arr = var->x / TILE_SIZE;
	if (var->x % TILE_SIZE < TILE_SIZE / 2)
		var->x_arr--;
	dist = sqrt((var->count_x - 100) * (var->count_x - 100)
			+ (var->count_y - 100) * (var->count_y - 100));
	if (dist <= 100)
	{
		if (dist > 94)
			*color = 0xa65f32;
		else if (var->x_arr < 0 || var->y_arr < 0 || var->x_arr
			> (int)game->map_width - 1
			|| var->y_arr > (int)game->map_height - 1
			|| game->map[var->y_arr][var->x_arr] == VOID)
			*color = 0xd99282;
		else if (game->map[var->y_arr][var->x_arr] == WALL)
			*color = 0x000000;
		else
			*color = 0xffffff;
		img->start_x = var->count_x + 842;
		img->start_y = var->count_y + 10;
		img->end_x = img->start_x + 1;
		img->end_y = img->start_y + 1;
	}
}

void	rend_minimap(t_cub3d *game, t_img_rendering *img)
{
	int			color;
	t_minimap	var;

	var.count_y = 0;
	var.y = game->player.y - 100;
	color = 0x000000;
	while (var.y < game->player.y + 100)
	{
		var.x = game->player.x - 100;
		var.count_x = 0;
		var.y_arr = var.y / TILE_SIZE;
		if (var.y % TILE_SIZE < TILE_SIZE / 2)
			var.y_arr--;
		while (var.x < game->player.x + 100)
		{
			rend_minimap_looping(game, img, &var, &color);
			img->color = color;
			set_the_pixel_looping(game, img);
			var.x++;
			var.count_x++;
		}
		var.count_y++;
		var.y++;
	}
}

void	rend_player_on_the_minimap(t_cub3d *game, t_img_rendering *img)
{
	int	x;
	int	y;

	x = 942;
	y = 110;
	img->start_x = x + (PLAYER_SIZE / 2);
	img->start_y = y + (PLAYER_SIZE / 2);
	img->end_x = img->start_x + PLAYER_SIZE;
	img->end_y = img->start_y + PLAYER_SIZE;
	img->color = 0xa65f32;
	set_the_pixel_looping(game, img);
}
