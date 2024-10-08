/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgebetsb <bgebetsb@students.42vienna.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:59:00 by bgebetsb          #+#    #+#             */
/*   Updated: 2024/09/20 13:36:08 by bgebetsb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	atoi_positive(const char **format)
{
	long long	sum;

	sum = 0;
	while (**format >= '0' && **format <= '9')
	{
		sum = sum * 10 + (**format - '0');
		if (sum > INT_MAX)
			return (-1);
		(*format)++;
	}
	return (sum);
}

void	parse_precision(const char **format, t_properties *prop, va_list *args)
{
	if (ft_strchr(".", **format))
	{
		prop->flags[((**format % 3) * 2) + (**format % 2)] = 1;
		(*format)++;
		if (**format == '*')
		{
			prop->precision = va_arg(*args, int);
			if (prop->precision < 0)
				prop->flags[2] = 0;
			(*format)++;
		}
		else
			prop->precision = atoi_positive(format);
	}
}

void	parse_width(const char **format, t_properties *prop, va_list *args)
{
	if (**format == '*')
	{
		prop->width = va_arg(*args, int);
		if (prop->width < 0)
		{
			prop->width = -prop->width;
			prop->flags[1] = 1;
		}
		(*format)++;
	}
	else
		prop->width = atoi_positive(format);
}

/*
 * ASCII Shenanigans
 * flags[0] = 0
 * flags[1] = -
 * flags[2] = .
 * flags[3] = +
 * flags[4] = SPACE
 * flags[5] = #
*/
t_properties	*parse_format(const char **format, va_list *args)
{
	t_properties	*properties;
	char			*flags;

	(*format)++;
	properties = (t_properties *)ft_calloc(1, sizeof(t_properties));
	if (properties == NULL)
		return (NULL);
	flags = (char *)ft_calloc(6, sizeof(char));
	if (flags == NULL)
		return (free(properties), NULL);
	while (ft_strchr("-0# +", **format))
	{
		flags[((**format % 3) * 2) + (**format % 2)] = 1;
		(*format)++;
	}
	properties->flags = flags;
	parse_width(format, properties, args);
	parse_precision(format, properties, args);
	if (flags[1])
		flags[0] = 0;
	if (properties->width == -1)
		return (free(flags), free(properties), NULL);
	properties->type = **format;
	(*format)++;
	return (properties);
}
