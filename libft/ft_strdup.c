/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgebetsb <bgebetsb@students.42vienna.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:06:05 by bgebetsb          #+#    #+#             */
/*   Updated: 2024/04/04 13:51:46 by bgebetsb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	size_t	length;
	char	*newstr;

	length = ft_strlen(s);
	newstr = (char *)ft_calloc(length + 1, sizeof(char));
	if (newstr == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (i < length)
	{
		newstr[i] = s[i];
		i++;
	}
	return (newstr);
}
