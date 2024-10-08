/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgebetsb <bgebetsb@students.42vienna.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:50:47 by bgebetsb          #+#    #+#             */
/*   Updated: 2024/04/22 09:50:49 by bgebetsb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_length(int n, t_properties *properties)
{
	int		prefix_space_or_plus;
	int		zero_and_no_precision;
	int		length;

	if (properties->flags[2] && properties->precision == 0 && n == 0)
		return (0);
	length = 1;
	if (n < 0 || properties->flags[3] || properties->flags[4])
	{
		length++;
	}
	while (n < -9 || n > 9)
	{
		length++;
		n /= 10;
	}
	prefix_space_or_plus = (properties->flags[3] || properties->flags[4]);
	zero_and_no_precision = (!properties->flags[2] && properties->flags[0]);
	if (properties->precision >= length)
		length = properties->precision + (n < 0 || prefix_space_or_plus);
	else if (zero_and_no_precision && properties->width > length)
		length = properties->width;
	return (length);
}

static void	fill_recursive(int n, t_properties *prop, char *str, int remaining)
{
	char	c;

	remaining--;
	if (n < 0)
		c = -(n % -10) + '0';
	else
		c = (n % 10) + '0';
	*str = c;
	if (n < -9 || n > 9)
		fill_recursive(n / 10, prop, str - 1, remaining);
	else
	{
		while (remaining-- > (n < 0))
			*(--str) = '0';
		if (n < 0)
			*(--str) = '-';
		else if (prop->flags[3])
			*str = '+';
		else if (prop->flags[4])
			*str = ' ';
	}
}

char	*ft_itoa_printf(int n, t_properties *properties)
{
	int		num_length;
	ssize_t	allocated;
	int		pos;
	char	*nb_str;

	num_length = count_length(n, properties);
	allocated = num_length;
	if (properties->width > allocated)
		allocated = properties->width;
	nb_str = ft_calloc(allocated + 1, sizeof(char));
	if (nb_str == NULL)
		return (NULL);
	if (properties->flags[1])
		pos = num_length - 1;
	else
		pos = allocated - 1;
	if (num_length > 0)
		fill_recursive(n, properties, nb_str + pos, num_length);
	if (allocated > num_length)
		ft_memset(nb_str + (properties->flags[1] * num_length),
			' ', allocated - num_length);
	return (nb_str);
}
