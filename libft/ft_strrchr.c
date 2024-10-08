/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgebetsb <bgebetsb@students.42vienna.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:17:56 by bgebetsb          #+#    #+#             */
/*   Updated: 2024/04/03 12:22:53 by bgebetsb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*tmp;

	tmp = (char *)s;
	tmp += ft_strlen(s);
	while (tmp >= s)
	{
		if (*tmp == (char)c)
		{
			return (tmp);
		}
		tmp--;
	}
	return (NULL);
}
