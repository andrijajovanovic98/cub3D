/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgebetsb <bgebetsb@students.42vienna.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:50:14 by bgebetsb          #+#    #+#             */
/*   Updated: 2024/04/22 09:50:17 by bgebetsb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_length(size_t n, t_properties *properties, t_chars c)
{
	int		length;
	int		prefix_space_or_plus;
	int		zero_and_no_precision;
	size_t	base;

	if (properties->flags[2] && properties->precision == 0 && n == 0)
		return (0);
	base = ft_strlen(c.charset);
	length = 1;
	if (properties->flags[3] || properties->flags[4])
		length++;
	while (n > base - 1)
	{
		length++;
		n /= base;
	}
	prefix_space_or_plus = (properties->flags[3] || properties->flags[4]);
	zero_and_no_precision = (!properties->flags[2] && properties->flags[0]);
	if (properties->precision > length)
		length = properties->precision + prefix_space_or_plus;
	else if (zero_and_no_precision && properties->width > length)
		length = properties->width;
	return (length);
}

static void	fill_recursive(size_t n, char *nb_str, t_chars c, int remaining)
{
	size_t	base;

	base = ft_strlen(c.charset);
	remaining--;
	*nb_str = c.charset[n % base];
	if (n > base - 1)
	{
		fill_recursive(n / base, nb_str - 1, c, remaining);
	}
	else
	{
		while (remaining-- > 0)
			*(--nb_str) = '0';
		if (c.prefix != NULL)
		{
			ft_memcpy(nb_str, c.prefix, ft_strlen(c.prefix));
		}
	}
}

char	*ft_itoa_base(size_t n, t_properties *properties, t_chars c)
{
	int			length;
	ssize_t		allocated;
	char		*nb_str;
	int			pos;

	length = count_length(n, properties, c);
	if (c.prefix && n != 0)
		length += 2;
	if (c.prefix && n == 0)
		c.prefix = NULL;
	allocated = length;
	if (properties->width > allocated)
		allocated = properties->width;
	nb_str = (char *)ft_calloc(allocated + 1, sizeof(char));
	if (nb_str == NULL)
		return (NULL);
	pos = allocated - 1 - (properties->flags[1] * (allocated - length));
	if (length > 0)
		fill_recursive(n, nb_str + pos, c, length);
	if (allocated > length)
		ft_memset(nb_str + (properties->flags[1] * length),
			' ', allocated - length);
	return (nb_str);
}
