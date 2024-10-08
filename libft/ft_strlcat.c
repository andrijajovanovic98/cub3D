/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgebetsb <bgebetsb@students.42vienna.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:03:30 by bgebetsb          #+#    #+#             */
/*   Updated: 2024/04/03 11:58:40 by bgebetsb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	src_length;
	size_t	dst_length;

	src_length = ft_strlen(src);
	if (size == 0)
	{
		return (src_length);
	}
	dst_length = ft_strlen(dst);
	if (dst_length <= size - 1)
	{
		ft_strlcpy(dst + dst_length, src, size - dst_length);
		return (src_length + dst_length);
	}
	return (src_length + size);
}
