/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:22:07 by ajovanov          #+#    #+#             */
/*   Updated: 2024/09/24 10:22:09 by ajovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

bool	close_to_door(size_t y1, size_t x1, size_t y2, size_t x2)
{
	size_t	y_diff;
	size_t	x_diff;

	if (y1 > y2)
		y_diff = y1 - y2;
	else
		y_diff = y2 - y1;
	if (x1 > x2)
		x_diff = x1 - x2;
	else
		x_diff = x2 - x1;
	if (TILE_SIZE * 2 < sqrt(x_diff * x_diff + y_diff * y_diff))
		return (false);
	return (true);
}

static bool	door_hit(t_maptype type, double percent_closed,
	double ver_rest, double hor_rest)
{
	if (type == DOOR_NORTHSOUTH
		&& (hor_rest <= round(TILE_SIZE * percent_closed)
			|| hor_rest >= round(TILE_SIZE * (1 - percent_closed))))
		return (true);
	else if (type == DOOR_WESTEAST
		&& (ver_rest <= round(TILE_SIZE * percent_closed)
			|| ver_rest >= round(TILE_SIZE * (1 - percent_closed))))
		return (true);
	return (false);
}

int	is_wall(const t_cub3d *game, float x, float y, bool checkDiagonal)
{
	int		hor;
	double	hor_rest;
	double	ver_rest;
	int		ver;

	hor = (int)round(x) / TILE_SIZE;
	ver = (int)round(y) / TILE_SIZE;
	if ((size_t)hor >= game->map_width || (size_t)ver
		>= game->map_height || ver < 0 || hor < 0)
		return (1);
	hor_rest = (int)round(y) % TILE_SIZE + 0.5;
	ver_rest = (int)round(x) % TILE_SIZE + 0.5;
	if (checkDiagonal && (!going_through_walls_check(game, ver, hor)))
		return (1);
	if (game->map[ver][hor] == WALL
		|| (checkDiagonal && too_close_to_wall(game, y, x)))
		return (1);
	if (game->map[ver][hor] == DOOR_NORTHSOUTH
		|| game->map[ver][hor] == DOOR_WESTEAST)
	{
		return (door_hit(game->map[ver][hor],
			game->doors[ver][hor].percent_closed / 2, ver_rest, hor_rest) * 2);
	}
	return (0);
}

t_wall	*get_current_wall(t_cub3d *game, t_raycasting *var, t_ray *ray)
{
	t_wall	*current_wall;

	if (ray->side == 0)
		var->wall_x = game->ray.pos_x + var->perp_walldist * ray->raydir_y;
	else
		var->wall_x = game->ray.pos_y + var->perp_walldist * ray->raydir_x;
	var->wall_x -= floor(var->wall_x);
	if (ray->side == 0)
	{
		if ((ray->raydir_x > 0) != game->texture_flipped)
			current_wall = &game->walls.wall_e;
		else
			current_wall = &game->walls.wall_w;
	}
	else
	{
		if ((ray->raydir_y > 0) != game->texture_flipped)
			current_wall = &game->walls.wall_s;
		else
			current_wall = &game->walls.wall_n;
	}
	if (ray->door)
		current_wall = &game->walls.door;
	return (current_wall);
}

void	get_wall_height(t_raycasting *var)
{
	var->perp_walldist *= 0.02;
	var->lineheight = (int)(WIN_HEIGHT / var->perp_walldist);
	var->drawstart = -var->lineheight / 2 + WIN_HEIGHT / 2;
	if (var->drawstart < 0)
		var->drawstart = 0;
	var->drawend = var->lineheight / 2 + WIN_HEIGHT / 2;
	if (var->drawend >= WIN_HEIGHT)
		var->drawend = WIN_HEIGHT - 1;
}
