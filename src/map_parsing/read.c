/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgebetsb <bgebetsb@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 20:51:33 by bgebetsb          #+#    #+#             */
/*   Updated: 2024/09/22 16:35:05 by bgebetsb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	properties_loaded(t_cub3d *cub3d)
{
	const t_textures	*textures;

	if (cub3d->ceiling_color == 0 || cub3d->floor_color == 0)
		return (false);
	textures = &cub3d->textures;
	return (textures->north != NULL && textures->south != NULL
		&& textures->east != NULL && textures->west != NULL);
}

static bool	read_properties(t_cub3d *cub3d, int fd)
{
	t_element	element;
	char		*line;
	int			i;

	if (properties_loaded(cub3d))
		return (true);
	if (!get_next_line(fd, &line, false))
		return (false);
	else if (line == NULL)
		return (errmsg(INCOMPLETE), false);
	if (line[0] != '\n')
	{
		i = -1;
		while (++i < 6 && ft_strncmp(line, cub3d->elements[i].string,
				ft_strlen(cub3d->elements[i].string) != 0));
		if (i == 6)
			return (free(line), errmsg(INCOMPLETE), false);
		element = cub3d->elements[i];
		if (ft_strncmp(line, element.string, ft_strlen(element.string)) != 0)
			return (free(line), errmsg(INVALID), false);
		if (!element.validate_func(element.variable, line))
			return (free(line), false);
	}
	return (free(line), read_properties(cub3d, fd));
}

static t_string	*read_map_string(t_cub3d *cub3d, int fd, t_string *map_string)
{
	char		*line;

	while (true)
	{
		if (!get_next_line(fd, &line, false)
			|| (line == NULL && map_string == NULL))
			return (string_clear(&map_string), NULL);
		if (line == NULL)
			return (return_string(map_string));
		if (line[0] == '\n')
		{
			free(line);
			if (map_string)
				return (errmsg(UNEXPECTED_END), string_clear(&map_string),
					NULL);
			continue ;
		}
		if (!valid_chars(cub3d, line, map_string) || only_space(line))
			return (free(line), string_clear(&map_string), NULL);
		remove_linebreak(line);
		map_string = string_append(map_string, line, ft_strlen(line));
		if (!map_string)
			return (NULL);
	}
}

bool	read_map(int argc, char **argv, t_cub3d *cub3d)
{
	t_string	*map_string;
	int			fd;
	bool		ret;

	fd = open_map(argc, argv);
	if (fd == -1)
		return (false);
	ret = read_properties(cub3d, fd);
	if (!ret)
		return (close(fd), false);
	map_string = read_map_string(cub3d, fd, NULL);
	close(fd);
	if (map_string == NULL)
		return (false);
	fill_map(cub3d, map_string);
	string_clear(&map_string);
	return (cub3d->map != NULL && cub3d->doors != NULL);
}
