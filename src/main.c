/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgebetsb <bgebetsb@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:11:50 by bgebetsb          #+#    #+#             */
/*   Updated: 2024/09/23 17:04:36 by bgebetsb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_window(t_cub3d *game)
{
	game->mlx_ptr = mlx_init();
	if (game->mlx_ptr == NULL)
		return (errmsg(MLXINIT), 1);
	game->win_ptr = mlx_new_window(game->mlx_ptr,
			WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (game->win_ptr == NULL)
		return (errmsg(WINDOWSINIT), 1);
	mlx_mouse_move(game->mlx_ptr, game->win_ptr, WIN_WIDTH / 2,
		WIN_HEIGHT / 2);
	game->mouse_pos.x = WIN_WIDTH / 2;
	game->mouse_pos.y = WIN_HEIGHT / 2;
	mlx_mouse_hide(game->mlx_ptr, game->win_ptr);
	return (0);
}

int	load_images(t_cub3d *game, t_wall *wall_n, char *str)
{
	wall_n->img_ptr = mlx_xpm_file_to_image(
			game->mlx_ptr, str, &wall_n->img_width, &wall_n->img_height);
	if (!wall_n->img_ptr || wall_n->img_width != 64 || wall_n->img_height != 64)
	{
		return (errmsg(TEXTURE), 1);
	}
	wall_n->img_data = mlx_get_data_addr
		(wall_n->img_ptr, &wall_n->bpp, &wall_n->line_length, &wall_n->endian);
	if (!wall_n->img_data)
	{
		return (errmsg(TEXTURE), 1);
	}
	wall_n->img_data = mlx_get_data_addr
		(wall_n->img_ptr, &wall_n->bpp, &wall_n->line_length, &wall_n->endian);
	if (!wall_n->img_data)
	{
		return (errmsg(TEXTURE), 1);
	}
	return (0);
}

bool	load_textures(t_cub3d *game)
{
	if (load_images(game, &game->walls.wall_n, game->textures.north) == 1)
		return (false);
	if (load_images(game, &game->walls.wall_s, game->textures.south) == 1)
		return (false);
	if (load_images(game, &game->walls.wall_e, game->textures.east) == 1)
		return (false);
	if (load_images(game, &game->walls.wall_w, game->textures.west) == 1)
		return (false);
	if (load_images(game, &game->walls.door, "./walls/door.xpm") == 1)
		return (false);
	return (true);
}

bool	get_new_image(t_cub3d *game)
{
	game->img.img_ptr = mlx_new_image(game->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (game->img.img_ptr == NULL)
		return (errmsg(XLM_IMAGE), false);
	game->img.img_data = mlx_get_data_addr(game->img.img_ptr, &game->img.bpp,
			&game->img.size_line, &game->img.endian);
	if (game->img.img_data == NULL)
		return (errmsg(IMG_DATA), false);
	return (true);
}

int	main(int argc, char **argv)
{
	t_cub3d	game;

	ft_memset(&game, 0, sizeof(t_cub3d));
	init_elements(&game);
	if (!read_map(argc, argv, &game))
		return (free_all(&game, -1), 1);
	if (!map_closed(&game))
		return (errmsg(NOT_CLOSED), free_all(&game, -1), 1);
	if (init_window(&game) == 1)
		return (free_all(&game, -1), 1);
	if (!load_sprites(&game))
		return (free_all(&game, -1), errmsg(SPRITES_FAILED), 1);
	if (!load_textures(&game))
		return (free_all(&game, -1), 1);
	if (!get_new_image(&game))
		return (free_all(&game, -1), 1);
	mlx_hook(game.win_ptr, 2, 1L << 0, handle_keypress, &game);
	mlx_hook(game.win_ptr, 17, 0, mlx_loop_end, game.mlx_ptr);
	mlx_mouse_hook(game.win_ptr, handle_mouse_click, &game);
	mlx_loop_hook(game.mlx_ptr, handle_loop_hook, &game);
	draw_map(&game, &game.img);
	mlx_loop(game.mlx_ptr);
	free_all(&game, -1);
}
