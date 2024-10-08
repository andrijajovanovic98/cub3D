/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgebetsb <bgebetsb@students.42vienna.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:16:13 by bgebetsb          #+#    #+#             */
/*   Updated: 2024/04/04 12:22:30 by bgebetsb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static size_t	count_length(int n)
{
	if (n < -9 || n > 9)
	{
		return (1 + count_length(n / 10));
	}
	return (1);
}

static void	fill_recursive(int n, char *nb_str, size_t pos)
{
	if (n < 0)
	{
		nb_str[pos] = -(n % -10) + '0';
		if (n < -9)
		{
			fill_recursive(n / 10, nb_str, --pos);
		}
	}
	else
	{
		nb_str[pos] = n % 10 + '0';
		if (n > 9)
		{
			fill_recursive(n / 10, nb_str, --pos);
		}
	}
}

char	*ft_itoa(int n)
{
	size_t			length;
	char			*nb_str;
	size_t			pos;

	length = count_length(n);
	if (n < 0)
	{
		length++;
	}
	nb_str = (char *)ft_calloc(length + 1, sizeof(char));
	if (nb_str == NULL)
	{
		return (NULL);
	}
	pos = length - 1;
	fill_recursive(n, nb_str, pos);
	if (n < 0)
	{
		nb_str[0] = '-';
	}
	return (nb_str);
}
