/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgebetsb <bgebetsb@students.42vienna.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:24:36 by bgebetsb          #+#    #+#             */
/*   Updated: 2024/04/03 15:44:28 by bgebetsb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_len;

	if (s == NULL)
	{
		return (NULL);
	}
	s_len = ft_strlen(s);
	if (start >= s_len || len == 0)
	{
		return (ft_calloc(1, sizeof(char)));
	}
	if (s_len - start < len)
	{
		len = s_len - start;
	}
	substr = ft_calloc(++len, sizeof(char));
	if (substr == NULL)
	{
		return (NULL);
	}
	ft_strlcpy(substr, s + start, len);
	return (substr);
}
