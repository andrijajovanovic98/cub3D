/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_str_handlers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgebetsb <bgebetsb@students.42vienna.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:32:48 by bgebetsb          #+#    #+#             */
/*   Updated: 2024/04/22 12:32:49 by bgebetsb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	handle_string(t_string **string, t_properties *prop, va_list *args)
{
	char	*str;
	char	*newstr;
	int		length;
	int		alloc;

	str = va_arg(*args, char *);
	if (str == NULL)
	{
		length = 0 + ((!prop->flags[2] || prop->precision >= 6) * 6);
		str = "(null)";
	}
	else
		length = ft_strlen(str);
	if (prop->flags[2] && prop->precision < length)
		length = prop->precision;
	alloc = length + (prop->width > length) * (prop->width - length);
	newstr = ft_calloc(alloc + 1, sizeof(char));
	if (newstr != NULL)
	{
		ft_memset(newstr, ' ', alloc);
		ft_memcpy(newstr + (!(prop->flags[1])) * (alloc - length), str, length);
		*string = string_append(*string, newstr, ft_strlen(newstr));
	}
	else
		string_clear(string);
}

void	handle_char(t_string **string, t_properties *properties, va_list *args)
{
	int		c;
	char	*str;
	int		width;

	c = va_arg(*args, int);
	width = 1;
	if (properties->width > 1)
		width = properties->width;
	str = malloc(width);
	if (str == NULL)
	{
		string_clear(string);
		return ;
	}
	ft_memset(str, ' ', width);
	if (str != NULL)
	{
		if (properties->flags[1])
			str[0] = (char)c;
		else
			str[width - 1] = (char)c;
		*string = string_append(*string, str, width);
	}
}

void	handle_percent(t_string **string)
{
	char	*str;

	str = ft_calloc(1, sizeof(char));
	if (str != NULL)
	{
		str[0] = '%';
		*string = string_append(*string, str, 1);
	}
}
