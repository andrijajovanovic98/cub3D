/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgebetsb <bgebetsb@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:58:17 by bgebetsb          #+#    #+#             */
/*   Updated: 2024/10/08 12:58:19 by bgebetsb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	going_through_walls_check(const t_cub3d *game, int new_y, int new_x)
{
	int	oldy;
	int	oldx;

	if (new_x <= 0 || new_y <= 0 || (size_t)new_y >= game->map_height - 1
		|| (size_t)new_x >= game->map_width - 1)
		return (false);
	oldy = game->player.y / TILE_SIZE;
	oldx = game->player.x / TILE_SIZE;
	if (oldy == new_y || oldx == new_x)
		return (true);
	if (game->map[new_y][oldx] == WALL || game->map[new_y][oldx] == VOID
		|| game->map[oldy][new_x] == WALL || game->map[oldy][new_x] == VOID)
		return (false);
	return (true);
}

bool	too_close_to_wall(const t_cub3d *game, int y, int x)
{
	return (game->map[(y + 5) / TILE_SIZE][x / TILE_SIZE] == WALL
		|| game->map[(y - 5) / TILE_SIZE][x / TILE_SIZE] == WALL
		|| game->map[y / TILE_SIZE][(x - 5) / TILE_SIZE] == WALL
		|| game->map[y / TILE_SIZE][(x + 5) / TILE_SIZE] == WALL);
}
