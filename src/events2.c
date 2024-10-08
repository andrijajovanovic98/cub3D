/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:52:07 by ajovanov          #+#    #+#             */
/*   Updated: 2024/09/24 12:52:09 by ajovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

bool	mouse_pos_changed(t_cub3d *game)
{
	int		x;
	int		y;
	int		x_diff;

	if (game->mouse_disabled)
		return (false);
	mlx_mouse_get_pos(game->mlx_ptr, game->win_ptr, &x, &y);
	if (x != game->mouse_pos.x || y != game->mouse_pos.y)
	{
		x_diff = game->mouse_pos.x - x;
		mlx_mouse_move(game->mlx_ptr, game->win_ptr, WIN_WIDTH / 2,
			WIN_HEIGHT / 2);
		game->mouse_pos.x = WIN_WIDTH / 2;
		game->mouse_pos.y = WIN_HEIGHT / 2;
		if (x_diff == 0)
			return (false);
		game->player.angle -= (1 / (double)WIN_WIDTH) * x_diff * 2;
		return (true);
	}
	return (false);
}

int	handle_mouse_click(int button, int x, int y, t_cub3d *game)
{
	(void)x;
	(void)y;
	if (button == 1)
	{
		game->sprite_index++;
		draw_map(game, &game->img);
	}
	return (0);
}

void	close_open_door(t_cub3d *game, size_t posy, size_t posx, bool *redraw)
{
	if (game->doors[posy][posx].state == CLOSING)
	{
		game->doors[posy][posx].percent_closed += 0.03;
		*redraw = true;
		if (game->doors[posy][posx].percent_closed >= 1.0)
			game->doors[posy][posx].state = IDLE;
	}
	else if (game->doors[posy][posx].state == OPENING)
	{
		game->doors[posy][posx].percent_closed -= 0.03;
		*redraw = true;
		if (game->doors[posy][posx].percent_closed <= 0.0)
			game->doors[posy][posx].state = IDLE;
	}
}

void	check_doors(t_cub3d *game)
{
	size_t	posy;
	size_t	posx;

	posy = 0;
	while (posy < game->map_height)
	{
		posx = 0;
		while (posx < game->map_width)
		{
			if (game->doors[posy][posx].state != NO_DOOR)
			{
				if (close_to_door(game->player.y, game->player.x,
						posy * TILE_SIZE + (TILE_SIZE / 2),
						posx * TILE_SIZE + (TILE_SIZE / 2)))
					game->doors[posy][posx].state = OPENING;
				else if (game->doors[posy][posx].percent_closed <= 0.0
					&& !close_to_door(game->player.y, game->player.x,
					posy * TILE_SIZE + (TILE_SIZE / 2),
					posx * TILE_SIZE + (TILE_SIZE / 2)))
					game->doors[posy][posx].state = CLOSING;
			}
			posx++;
		}
		posy++;
	}
}

bool	update_doors(t_cub3d *game)
{
	size_t	posy;
	size_t	posx;
	bool	redraw;

	posy = 0;
	redraw = false;
	while (posy < game->map_height)
	{
		posx = 0;
		while (posx < game->map_width)
		{
			close_open_door(game, posy, posx, &redraw);
			posx++;
		}
		posy++;
	}
	return (redraw);
}
