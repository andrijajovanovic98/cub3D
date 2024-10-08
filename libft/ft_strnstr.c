/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgebetsb <bgebetsb@students.42vienna.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:19:19 by bgebetsb          #+#    #+#             */
/*   Updated: 2024/04/03 11:50:01 by bgebetsb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static	size_t	get_min(size_t nb1, size_t nb2)
{
	if (nb2 < nb1)
	{
		return (nb2);
	}
	else
	{
		return (nb1);
	}
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	little_len;
	size_t	i;
	size_t	j;

	little_len = ft_strlen(little);
	if (little_len == 0)
		return ((char *)big);
	if ((big == NULL && len == 0) || little_len > ft_strlen(big))
		return (NULL);
	i = 0;
	while (len > 0 && i < get_min(ft_strlen(big), len))
	{
		j = 0;
		while (big[i + j] == little[j] && j < little_len && i + j < len)
		{
			j++;
			if (j == little_len)
				return ((char *)(big + i));
		}
		i++;
	}
	return (NULL);
}
