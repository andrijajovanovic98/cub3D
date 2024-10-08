/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgebetsb <bgebetsb@students.42vienna.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:44:36 by bgebetsb          #+#    #+#             */
/*   Updated: 2024/04/04 11:53:17 by bgebetsb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*buf;
	size_t			length;
	unsigned int	i;

	if (s == NULL)
	{
		return (NULL);
	}
	length = ft_strlen(s);
	buf = (char *)ft_calloc(length + 1, sizeof(char));
	if (buf == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (s[i])
	{
		buf[i] = f(i, s[i]);
		i++;
	}
	return (buf);
}
