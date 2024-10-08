/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgebetsb <bgebetsb@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:38:27 by bgebetsb          #+#    #+#             */
/*   Updated: 2024/09/26 13:38:29 by bgebetsb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_start(t_maptype type)
{
	if (type == START_NORTH || type == START_SOUTH || type == START_WEST
		|| type == START_EAST)
		return (true);
	return (false);
}

bool	only_space(char *str)
{
	while (*str)
	{
		if (*str == '\n')
			return (ft_putstr_fd(ONLY_SPACE, 2), true);
		if (*str != ' ')
			return (false);
		str++;
	}
	return (ft_putstr_fd(ONLY_SPACE, 2), true);
}
