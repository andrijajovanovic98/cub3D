/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgebetsb <bgebetsb@students.42vienna.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:41:52 by bgebetsb          #+#    #+#             */
/*   Updated: 2024/04/06 21:04:07 by bgebetsb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem;
	size_t	total_size;

	if (nmemb == 0 || size == 0)
	{
		return (malloc(0));
	}
	total_size = nmemb * size;
	if (total_size / size != nmemb)
	{
		return (NULL);
	}
	mem = malloc(total_size);
	if (mem == NULL)
	{
		perror("Error\ncub3d");
		return (NULL);
	}
	ft_bzero(mem, total_size);
	return (mem);
}
