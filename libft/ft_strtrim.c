/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgebetsb <bgebetsb@students.42vienna.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:47:34 by bgebetsb          #+#    #+#             */
/*   Updated: 2024/04/03 17:13:49 by bgebetsb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char const	*tmp;
	char		*ret;

	if (s1 == NULL)
	{
		return (NULL);
	}
	while (*s1 && ft_strchr(set, *s1))
	{
		s1++;
	}
	tmp = s1 + ft_strlen(s1) - 1;
	while (tmp > s1 && ft_strchr(set, *tmp))
	{
		tmp--;
	}
	ret = (char *)ft_calloc(tmp - s1 + 2, sizeof(char));
	if (ret == NULL)
	{
		return (NULL);
	}
	ft_strlcpy(ret, s1, tmp - s1 + 2);
	return (ret);
}
