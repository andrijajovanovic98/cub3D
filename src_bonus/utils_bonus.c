/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgebetsb <bgebetsb@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 19:53:33 by bgebetsb          #+#    #+#             */
/*   Updated: 2024/09/23 16:41:56 by bgebetsb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	skip_spaces(const char *str, size_t *index)
{
	while (str[*index] == ' ')
		(*index)++;
}

static void	destroy_mlx(t_cub3d *game)
{
	if (game->win_ptr)
	{
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		game->win_ptr = NULL;
	}
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
		game->mlx_ptr = NULL;
	}
}

void	free_all(t_cub3d *cub3d, int fd)
{
	size_t	i;

	destroy_images(cub3d);
	free(cub3d->textures.north);
	free(cub3d->textures.east);
	free(cub3d->textures.south);
	free(cub3d->textures.west);
	free_sprites(cub3d);
	get_next_line(fd, NULL, true);
	if (fd != -1)
		close(fd);
	i = 0;
	while (i < cub3d->map_height)
	{
		if (cub3d->doors)
			free(cub3d->doors[i]);
		if (cub3d->map)
			free(cub3d->map[i++]);
	}
	free(cub3d->doors);
	free(cub3d->map);
	destroy_mlx(cub3d);
}

void	destroy_images(t_cub3d *game)
{
	destroy_image(game->mlx_ptr, &game->walls.wall_n.img_ptr);
	destroy_image(game->mlx_ptr, &game->walls.wall_s.img_ptr);
	destroy_image(game->mlx_ptr, &game->walls.wall_e.img_ptr);
	destroy_image(game->mlx_ptr, &game->walls.wall_w.img_ptr);
	destroy_image(game->mlx_ptr, &game->walls.door.img_ptr);
	destroy_image(game->mlx_ptr, &game->img.img_ptr);
	free_sprites(game);
}
