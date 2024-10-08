/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgebetsb <bgebetsb@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 19:10:30 by bgebetsb          #+#    #+#             */
/*   Updated: 2024/09/20 19:10:31 by bgebetsb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	check_file_extension(const char *filename)
{
	size_t	length;
	char	*tmp;

	tmp = ft_strrchr(filename, '/');
	if (tmp)
		filename = tmp + 1;
	length = ft_strlen(filename);
	if (length < 5 || ft_strncmp(filename + length - 4, ".cub", 4) != 0)
		return (false);
	return (true);
}

int	open_map(int argc, char **argv)
{
	int		fd;

	if (argc != 2 || !check_file_extension(argv[1]))
		return (errmsg(USAGE), -1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		perror("Error\ncub3d");
	return (fd);
}
