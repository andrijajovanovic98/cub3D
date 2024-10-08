/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:20:22 by ajovanov          #+#    #+#             */
/*   Updated: 2024/10/07 17:20:25 by ajovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

int	w(int keycode, t_cub3d *game)
{
	double	angle;

	angle = game->player.angle;
	if (keycode == XK_w)
	{
		if (!is_wall(game, game->player.x + MOVE_CHECK * cos(angle),
				game->player.y + MOVE_CHECK * sin(angle), true))
		{
			game->player.x += MOVE_SPEED * cos(angle);
			game->player.y += MOVE_SPEED * sin(angle);
		}
		else if (!is_wall(game, game->player.x
				+ MOVE_CHECK * cos(angle), game->player.y, true))
			game->player.x += MOVE_SPEED / 2 * cos(angle);
		else if (!is_wall(game, game->player.x,
				game->player.y + MOVE_CHECK * sin(angle), true))
			game->player.y += MOVE_SPEED / 2 * sin(angle);
		else
			return (1);
		check_doors(game);
	}
	return (0);
}

int	a(int keycode, t_cub3d *game)
{
	double	angle;

	angle = game->player.angle;
	if (keycode == XK_s)
	{
		if (!is_wall(game, game->player.x - MOVE_CHECK * cos(angle),
				game->player.y - MOVE_CHECK * sin(angle), true))
		{
			game->player.x -= MOVE_SPEED * cos(angle);
			game->player.y -= MOVE_SPEED * sin(angle);
		}
		else if (!is_wall(game, game->player.x
				- MOVE_CHECK * cos(angle), game->player.y, true))
			game->player.x -= MOVE_SPEED / 2 * cos(angle);
		else if (!is_wall(game, game->player.x,
				game->player.y - MOVE_CHECK * sin(angle), true))
			game->player.y -= MOVE_SPEED / 2 * sin(angle);
		else
			return (1);
		check_doors(game);
	}
	return (0);
}

int	s(int keycode, t_cub3d *game)
{
	double		angle;
	static int	check;

	check = 0;
	angle = game->player.angle;
	if (keycode == XK_a)
	{
		if (!is_wall(game, game->player.x - MOVE_CHECK * cos(angle + M_PI / 2),
				game->player.y - MOVE_CHECK * sin(angle + M_PI / 2), true))
		{
			game->player.x -= MOVE_SPEED * cos(angle + M_PI / 2);
			game->player.y -= MOVE_SPEED * sin(angle + M_PI / 2);
		}
		else if (!is_wall(game, game->player.x
				- MOVE_CHECK * cos(angle + M_PI / 2), game->player.y, true))
			game->player.x -= MOVE_SPEED / 2 * cos(angle + M_PI / 2);
		else if (!is_wall(game, game->player.x,
				game->player.y - MOVE_CHECK * sin(angle + M_PI / 2), true))
			game->player.y -= MOVE_SPEED / 2 * sin(angle + M_PI / 2);
		else
			return (1);
		check_doors(game);
	}
	return (0);
}

int	d(int keycode, t_cub3d *game)
{
	double	angle;

	angle = game->player.angle;
	if (keycode == XK_d)
	{
		if (!is_wall(game, game->player.x + MOVE_CHECK * cos(angle + M_PI / 2),
				game->player.y + MOVE_CHECK * sin(angle + M_PI / 2), true))
		{
			game->player.x += MOVE_SPEED * cos(angle + M_PI / 2);
			game->player.y += MOVE_SPEED * sin(angle + M_PI / 2);
		}
		else if (!is_wall(game, game->player.x
				+ MOVE_CHECK * cos(angle + M_PI / 2), game->player.y, true))
			game->player.x += MOVE_SPEED / 2 * cos(angle + M_PI / 2);
		else if (!is_wall(game, game->player.x,
				game->player.y + MOVE_CHECK * sin(angle + M_PI / 2), true))
			game->player.y += MOVE_SPEED / 2 * sin(angle + M_PI / 2);
		else
			return (1);
		check_doors(game);
	}
	return (0);
}
