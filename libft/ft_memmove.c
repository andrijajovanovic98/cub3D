/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgebetsb <bgebetsb@students.42vienna.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:30:19 by bgebetsb          #+#    #+#             */
/*   Updated: 2024/04/03 11:33:16 by bgebetsb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;

	i = 0;
	if (dest == NULL && src == NULL && n > 0)
	{
		return (NULL);
	}
	while (i < n)
	{
		if (dest > src)
		{
			((char *)dest)[n - i - 1] = ((char *)src)[n - i - 1];
		}
		else
		{
			((char *)dest)[i] = ((char *)src)[i];
		}
		i++;
	}
	return (dest);
}
