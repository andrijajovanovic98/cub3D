/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgebetsb <bgebetsb@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 00:57:34 by bgebetsb          #+#    #+#             */
/*   Updated: 2024/09/22 22:00:50 by bgebetsb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_doors(t_door ***doors)
{
	size_t	i;

	i = 0;
	while (*doors && (*doors)[i])
		free((*doors)[i++]);
	free(*doors);
	*doors = NULL;
}

static void	allocate_doors(t_cub3d *game)
{
	size_t	posy;
	size_t	posx;

	game->doors = ft_calloc(game->map_height, sizeof(t_door *));
	if (!game->doors)
		return ;
	posy = 0;
	while (posy < game->map_height)
	{
		game->doors[posy] = ft_calloc(game->map_width, sizeof(t_door));
		if (!game->doors[posy])
			return (free_doors(&game->doors));
		posx = 0;
		while (posx < game->map_width)
		{
			game->doors[posy][posx].percent_closed = 1.0;
			if (game->map[posy][posx] == DOOR)
				game->doors[posy][posx].state = IDLE;
			else
				game->doors[posy][posx].state = NO_DOOR;
			posx++;
		}
		posy++;
	}
}

static void	allocate_map(t_cub3d *cub3d, const t_string *map_string)
{
	size_t	i;

	cub3d->map = ft_calloc(map_string->items, sizeof(t_maptype *));
	if (!cub3d->map)
		return ;
	i = 0;
	while (i < map_string->items)
	{
		cub3d->map[i] = ft_calloc(map_string->max_length, sizeof(t_maptype));
		if (!cub3d->map[i])
		{
			while (i-- > 0)
				free(cub3d->map[i]);
			free(cub3d->map);
			cub3d->map = NULL;
			return ;
		}
		i++;
	}
	cub3d->map_height = map_string->items;
	cub3d->map_width = map_string->max_length;
}

static t_maptype	match_char(char c)
{
	if (c == '0')
		return (SPACE);
	else if (c == '1')
		return (WALL);
	else if (c == ' ')
		return (VOID);
	else if (c == 'N')
		return (START_NORTH);
	else if (c == 'S')
		return (START_SOUTH);
	else if (c == 'W')
		return (START_WEST);
	else if (c == 'E')
		return (START_EAST);
	else if (c == 'D')
		return (DOOR);
	else
		return (UNKNOWN);
}

void	fill_map(t_cub3d *cub3d, const t_string *map_string)
{
	size_t			i;
	size_t			j;
	t_list			*cur;
	const t_strbuf	*strbuf;

	allocate_map(cub3d, map_string);
	if (!cub3d->map)
		return ;
	i = map_string->items;
	cur = map_string->buffers;
	while (i-- > 0)
	{
		j = 0;
		strbuf = (t_strbuf *)cur->content;
		while (j < strbuf->length)
		{
			cub3d->map[i][j] = match_char(strbuf->buf[j]);
			j++;
		}
		while (j < map_string->max_length)
			cub3d->map[i][j++] = VOID;
		cur = cur->next;
	}
	allocate_doors(cub3d);
}
