/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgebetsb <bgebetsb@students.42vienna.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 13:02:36 by bgebetsb          #+#    #+#             */
/*   Updated: 2024/04/17 21:24:54 by bgebetsb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static size_t	get_line_length(char *str)
{
	size_t	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i++] == '\n')
			return (i);
	}
	return (0);
}

static bool	get_line(char **str, size_t length, char **line)
{
	char	*rest;

	if (*str == NULL)
		return (*line = NULL, true);
	*line = (char *)ft_calloc(length + 1, sizeof(char));
	if (*line == NULL)
		return (free(*str), *str = NULL, false);
	if (gnl_strlen(*str) > length)
	{
		rest = (char *)ft_calloc(ft_strlen(*str) - length + 1, sizeof(char));
		if (rest == NULL)
			return (free(*str), *str = NULL, free(*line), *line = NULL, false);
		ft_strlcpy(rest, *str + length, ft_strlen(*str) - length + 1);
	}
	else
		rest = NULL;
	ft_strlcpy(*line, *str, length + 1);
	free(*str);
	*str = rest;
	return (true);
}

bool	get_next_line(int fd, char **line, bool freeing)
{
	static char	*cache = NULL;
	char		*buf;
	char		*tmp;
	ssize_t		ret;

	if (freeing)
		return (free(cache), cache = NULL, true);
	if (fd == -1 || BUFFER_SIZE < 1)
		return (false);
	if (get_line_length(cache))
		return (get_line(&cache, get_line_length(cache), line));
	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (buf == NULL)
		return (free(cache), cache = NULL, false);
	ret = read(fd, buf, BUFFER_SIZE);
	if (ret == -1)
		return (perror("Error\ncub3d"), free(cache), cache = NULL, free(buf),
			false);
	if (ret == 0)
		return (free(buf), get_line(&cache, gnl_strlen(cache), line));
	tmp = gnl_strjoin(cache, buf);
	free(buf);
	if (tmp == NULL)
		return (free(cache), cache = NULL, false);
	return (free(cache), cache = tmp, get_next_line(fd, line, false));
}
