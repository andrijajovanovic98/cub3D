/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgebetsb <bgebetsb@students.42vienna.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:38:30 by bgebetsb          #+#    #+#             */
/*   Updated: 2024/04/17 21:20:59 by bgebetsb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	gnl_strlen(char *str)
{
	size_t	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*gnl_strjoin(char *str1, char *str2)
{
	size_t	len1;
	size_t	len2;
	size_t	i;
	size_t	j;
	char	*newstr;

	len1 = gnl_strlen(str1);
	len2 = gnl_strlen(str2);
	newstr = ft_calloc(len1 + len2 + 1, sizeof(char));
	if (newstr == NULL)
		return (NULL);
	i = 0;
	while (str1 && i < len1)
	{
		newstr[i] = str1[i];
		i++;
	}
	j = 0;
	while (str2 && j < len2)
	{
		newstr[i + j] = str2[j];
		j++;
	}
	return (newstr);
}
