/* ************************************************************************** */
/*                                                                        */
/*                                                    :::      ::::::::   */
/*   elements.c                                     :+:      :+:    :+:   */
/*                                                +:+ +:+         +:+     */
/*   By: bgebetsb <bgebetsb@student.42vienna.com>   +#+  +:+   +#+        */
/*                                            +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 19:59:31 by bgebetsb      #+#    #+#             */
/*   Updated: 2024/09/21 00:44:27 by bgebetsb     ###   ########.fr       */
/*                                                                        */
/* ************************************************************************** */

#include "cub3d.h"

bool	validate_texture(void *ptr, char *line)
{
	char	**var;
	size_t	start;
	size_t	length;

	start = 2;
	skip_spaces(line, &start);
	if (start == 2 || line[start] == '\0' || line[start] == '\n')
		return (errmsg(INVALID), false);
	length = 0;
	while (line[start + length] && line[start + length] != '\n')
	{
		if (line[start + length] == ' ')
			return (errmsg(INVALID), false);
		length++;
	}
	var = (char **)ptr;
	if (*var)
		return (errmsg(REDECLARATION), false);
	*var = ft_substr(line, start, length);
	if (!*var)
		return (false);
	return (true);
}

bool	add_number(int *nbr, const char *line, size_t *pos)
{
	int16_t	sum;
	size_t	chars;

	sum = 0;
	chars = 0;
	while (line[*pos] >= '0' && line[*pos] <= '9')
	{
		if (sum == 0 && chars > 0)
			return (errmsg(INVALID_NUMBER), false);
		sum = sum * 10 + (line[*pos] - '0');
		if (sum > 255)
			return (errmsg(INVALID_NUMBER), false);
		(*pos)++;
		chars++;
	}
	if (chars == 0
		|| (line[*pos] != '\n' && line[*pos] != ' ' && line[*pos] != ','))
		return (errmsg(NUMBER_EXPECTED), false);
	*nbr += sum;
	return (true);
}

bool	validate_number(void *ptr, char *line)
{
	int		*var;
	size_t	i;
	int		digit;

	i = 1;
	skip_spaces(line, &i);
	if (i == 1 || line[i] == '\0' || line[i] == '\n')
		return (errmsg(INVALID), false);
	var = (int *)ptr;
	if (*var != 0)
		return (errmsg(REDECLARATION), false);
	digit = -1;
	while (++digit < 3)
	{
		*var <<= 8;
		skip_spaces(line, &i);
		if (!add_number(var, line, &i))
			return (false);
		skip_spaces(line, &i);
		if ((digit < 2 && line[i] != ',') || (digit == 2 && line[i] != '\n'))
			return (errmsg(NUMBER_EXPECTED), false);
		i++;
	}
	*var |= 0xFF000000;
	return (true);
}

static void	init_element(t_element *element, char *expected, void *variable,
							bool (*validate_func)(void *, char *))
{
	element->string = expected;
	element->variable = variable;
	element->validate_func = validate_func;
}

void	init_elements(t_cub3d *cub3d)
{
	init_element(&cub3d->elements[0], "NO", &cub3d->textures.north,
		validate_texture);
	init_element(&cub3d->elements[1], "SO", &cub3d->textures.south,
		validate_texture);
	init_element(&cub3d->elements[2], "EA", &cub3d->textures.east,
		validate_texture);
	init_element(&cub3d->elements[3], "WE", &cub3d->textures.west,
		validate_texture);
	init_element(&cub3d->elements[4], "C", &cub3d->ceiling_color,
		validate_number);
	init_element(&cub3d->elements[5], "F", &cub3d->floor_color,
		validate_number);
}
