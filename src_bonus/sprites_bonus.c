/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgebetsb <bgebetsb@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:42:48 by bgebetsb          #+#    #+#             */
/*   Updated: 2024/09/23 17:50:27 by bgebetsb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_sprites(t_cub3d *game)
{
	int	i;

	i = -1;
	while (++i < 5)
		destroy_image(game->mlx_ptr, &game->sprites[i].xpm);
}

bool	load_sprites(t_cub3d *game)
{
	char		filename[21];
	t_sprite	*sprite;
	int			i;

	ft_strlcpy(filename, "textures/pistol1.xpm", 21);
	i = -1;
	while (++i < 5)
	{
		sprite = &game->sprites[i];
		sprite->xpm = mlx_xpm_file_to_image(game->mlx_ptr, filename,
				&sprite->width, &sprite->height);
		if (!sprite->xpm
			|| sprite->width != 350 || sprite->height != 350)
			return (free_sprites(game), errmsg(XPM_ERROR), false);
		sprite->xpm_data = mlx_get_data_addr(sprite->xpm, &sprite->bpp,
				&sprite->size_line, &sprite->endian);
		filename[15] = i + 2 + '0';
	}
	return (true);
}

static void	*ft_memcpy_cube(void *dest, const void *src, size_t n)
{
	size_t	i;
	int		*dest_int;
	int		*src_int;

	i = 0;
	if (dest == NULL && src == NULL && n > 0)
		return (NULL);
	dest_int = (int *)dest;
	src_int = (int *)src;
	while (i < n)
	{
		if (src_int[i] != 0xFFFFFF)
			dest_int[i] = src_int[i];
		i++;
	}
	return (dest);
}

/*
	WIN_WIDTH * 2 because it should be in the middle (/ 2),
	but every pixel has 4 bytes
*/
void	put_sprite_to_image(t_cub3d *game)
{
	t_sprite	*sprite;
	int			y;
	int			offset;
	int			bigoffset;
	int			dest_x;

	y = -1;
	if (game->sprite_index == 5)
		game->sprite_index = 0;
	sprite = &game->sprites[game->sprite_index];
	dest_x = WIN_WIDTH * 2;
	dest_x -= dest_x % 4;
	while (++y < sprite->height)
	{
		offset = y * sprite->size_line;
		bigoffset = (y + WIN_HEIGHT - sprite->height)
			* game->img.size_line + dest_x;
		ft_memcpy_cube(game->img.img_data + bigoffset,
			sprite->xpm_data + offset, sprite->size_line / sprite->bpp * 8);
	}
}
