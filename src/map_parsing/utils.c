/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgebetsb <bgebetsb@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:34:56 by bgebetsb          #+#    #+#             */
/*   Updated: 2024/09/22 16:35:22 by bgebetsb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	remove_linebreak(char *str)
{
	size_t	length;

	length = ft_strlen(str);
	if (length > 0 && str[length - 1] == '\n')
		str[length - 1] = '\0';
}

t_string	*return_string(t_string *map_string)
{
	if (!valid_chars(NULL, NULL, map_string))
	{
		errmsg(MISSING_START);
		string_clear(&map_string);
		return (NULL);
	}
	return (map_string);
}
