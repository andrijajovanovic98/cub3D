/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgebetsb <bgebetsb@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 01:10:21 by bgebetsb          #+#    #+#             */
/*   Updated: 2024/09/23 11:32:35 by bgebetsb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	map_direction(char c)
{
	if (c == 'N')
		return (3 * M_PI / 2);
	else if (c == 'E')
		return (0);
	else if (c == 'S')
		return (M_PI / 2);
	else
		return (M_PI);
}

void	assign_player_start_values(t_cub3d *game, int x, int y)
{
	game->player.y_arr = y;
	game->player.y = y * TILE_SIZE + TILE_SIZE / 2;
	game->player.x_arr = x;
	game->player.x = x * TILE_SIZE + TILE_SIZE / 2;
	game->ray.pos_x = game->player.x;
	game->ray.pos_y = game->player.y;
}

bool	valid_chars(t_cub3d *cub3d, const char *line, const t_string *map_str)
{
	static bool	start_found = false;
	size_t		i;
	size_t		y;

	i = -1;
	y = 0;
	if (map_str)
		y = map_str->items;
	while (line && line[++i])
	{
		if (!ft_strchr("01 NSEW\n", line[i])
			&& (!DOOR_VALID || !ft_strchr("D", line[i])))
			return (errmsg(INVALID_CHAR), false);
		if (ft_strchr("NSEW", line[i]))
		{
			if (start_found)
				return (errmsg(DUPLICATE_START), false);
			assign_player_start_values(cub3d, i, y);
			cub3d->player.angle = map_direction(line[i]);
			start_found = true;
		}
	}
	return (line != NULL || start_found);
}

bool	door_check(t_maptype **map, size_t y, size_t x)
{
	if (map[y][x] == DOOR)
	{
		if (map[y - 1][x] == WALL && map[y + 1][x] == WALL)
			map[y][x] = DOOR_NORTHSOUTH;
		else if (map[y][x - 1] == WALL && map[y][x + 1] == WALL)
			map[y][x] = DOOR_WESTEAST;
		else
			return (false);
	}
	return (true);
}

bool	map_closed(const t_cub3d *cub3d)
{
	t_maptype	**map;
	size_t		y;
	size_t		x;

	map = cub3d->map;
	y = -1;
	while (++y < cub3d->map_height)
	{
		x = -1;
		while (++x < cub3d->map_width)
		{
			if (is_start(map[y][x]) || map[y][x] == DOOR || map[y][x] == SPACE)
			{
				if (y == 0 || x == 0 || x == cub3d->map_width - 1
					|| y == cub3d->map_height - 1)
					return (false);
				if (map[y - 1][x] == VOID || map[y + 1][x] == VOID
					|| map[y][x - 1] == VOID || map[y][x + 1] == VOID)
					return (false);
			}
			if (!door_check(map, y, x))
				return (false);
		}
	}
	return (true);
}
