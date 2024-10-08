/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:57:26 by ajovanov          #+#    #+#             */
/*   Updated: 2024/09/24 10:57:29 by ajovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	arrows(int keycode, t_cub3d *game)
{
	if (keycode == XK_Left)
	{
		game->player.angle -= 0.1;
	}
	if (keycode == XK_Right)
	{
		game->player.angle += 0.1;
	}
}

int	handle_keypress(int keycode, t_cub3d *game)
{
	w(keycode, game);
	a(keycode, game);
	s(keycode, game);
	d(keycode, game);
	arrows(keycode, game);
	if (keycode == XK_space)
		game->sprite_index++;
	else if (keycode == XK_k)
		game->mouse_disabled = !game->mouse_disabled;
	else if (keycode == XK_f)
		game->texture_flipped = !game->texture_flipped;
	draw_map(game, &game->img);
	if (keycode == XK_Escape)
		mlx_loop_end(game->mlx_ptr);
	return (0);
}

int	handle_loop_hook(t_cub3d *game)
{
	bool	redraw;

	redraw = false;
	if (game->sprite_index != 0)
	{
		redraw = true;
		game->sprite_index++;
	}
	if (mouse_pos_changed(game))
		redraw = true;
	if (update_doors(game))
		redraw = true;
	if (redraw)
		draw_map(game, &game->img);
	return (0);
}
