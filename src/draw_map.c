/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:06:05 by ajovanov          #+#    #+#             */
/*   Updated: 2024/09/24 10:06:08 by ajovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	draw_floor_and_ceiling(t_cub3d *game, int x, int drawstart, int drawend)
{
	t_set_pixel	pixel;
	int			y;

	y = 0;
	while (y < drawstart)
	{
		set_pixel_variables(&pixel, game->ceiling_color, x, y);
		set_pixel(game->img.img_data,
			pixel, game->img.size_line, game->img.bpp);
		y++;
	}
	y = drawend;
	while (y < WIN_HEIGHT)
	{
		set_pixel_variables(&pixel, game->floor_color, x, y);
		set_pixel(game->img.img_data,
			pixel, game->img.size_line, game->img.bpp);
		y++;
	}
}

void	choose_pixel_from_texture(t_ray *ray, int *texture_x)
{
	if (ray->side == 0 && ray->raydir_x > 0)
		*texture_x = ray->mapy % TILE_SIZE;
	if (ray->side == 0 && ray->raydir_x < 0)
		*texture_x = ray->mapy % TILE_SIZE;
	if (ray->side == 1 && ray->raydir_y < 0)
		*texture_x = ray->mapx % TILE_SIZE;
	if (ray->side == 1 && ray->raydir_y > 0)
		*texture_x = ray->mapx % TILE_SIZE;
}

void	draw_wall(t_cub3d *game,
			t_raycasting *var, t_wall *current_wall, t_ray *ray)
{
	int	texture_x;
	int	texture_y;
	int	y;
	int	d;
	int	color;

	current_wall = get_current_wall(game, var, ray);
	texture_x = (int)(var->wall_x * (double)current_wall->img_width);
	choose_pixel_from_texture(ray, &texture_x);
	y = var->drawstart;
	while (y < var->drawend)
	{
		d = y * 256 - WIN_HEIGHT * 128 + var->lineheight * 128;
		texture_y = ((d * current_wall->img_height) / var->lineheight) / 256;
		color = *(unsigned int *)(current_wall->img_data
				+ (texture_y * current_wall->line_length
					+ texture_x * (current_wall->bpp / 8)));
		set_pixel(game->img.img_data, (t_set_pixel){var->i, y, color},
			game->img.size_line, game->img.bpp);
		y++;
	}
}

void	draw_map(t_cub3d *game, t_img_rendering *img)
{
	cast_all_rays(game);
	rend_minimap(game, img);
	rend_player_on_the_minimap(game, img);
	put_sprite_to_image(game);
	mlx_put_image_to_window
		(game->mlx_ptr, game->win_ptr, game->img.img_ptr, 0, 0);
}
