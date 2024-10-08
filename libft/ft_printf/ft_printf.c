/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgebetsb <bgebetsb@students.42vienna.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:29:32 by bgebetsb          #+#    #+#             */
/*   Updated: 2024/09/20 13:41:52 by bgebetsb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	print_string(t_string **string, int fd)
{
	char	*str;
	size_t	length;

	str = string_get(*string);
	if (str == NULL)
		return (string_clear(string), -1);
	length = (*string)->total_length;
	write(fd, str, length);
	free(str);
	return (string_clear(string), length);
}

int	append_regular(const char **format, t_string **string)
{
	size_t	i;
	char	*str;

	i = 0;
	while ((*format)[i] && (*format)[i] != '%')
		i++;
	if ((*format)[i] == '%' && (*format)[i + 1] == '\0')
		return (string_clear(string), 0);
	if (i > 0)
	{
		str = ft_substr(*format, 0, i);
		if (str == NULL)
			return (string_clear(string), 0);
		*string = string_append(*string, str, i);
		if (*string == NULL)
			return (0);
		*format += i;
	}
	return (1);
}

void	handle_arg(t_string **string, t_properties **properties, va_list *args)
{
	if ((*properties)->type == 's')
		handle_string(string, *properties, args);
	else if ((*properties)->type == 'c')
		handle_char(string, *properties, args);
	else if ((*properties)->type == 'd' || (*properties)->type == 'i')
		handle_int(string, *properties, args);
	else if ((*properties)->type == 'u')
		handle_uint(string, *properties, args);
	else if ((*properties)->type == '%')
		handle_percent(string);
	else if ((*properties)->type == 'X' || (*properties)->type == 'x')
		handle_hex(string, *properties, args);
	else if ((*properties)->type == 'p')
		handle_pointer(string, *properties, args);
	free((*properties)->flags);
	free(*properties);
	*properties = NULL;
}

int	ft_printf(int fd, const char *format, ...)
{
	va_list			args;
	t_string		*string;
	t_properties	*properties;

	if (format == NULL)
		return (-1);
	if (!*format)
		return (0);
	string = NULL;
	va_start(args, format);
	while (*format)
	{
		if (!append_regular(&format, &string))
			return (va_end(args), -1);
		if (*format == '%')
		{
			properties = parse_format(&format, &args);
			if (properties == NULL)
				return (string_clear(&string), va_end(args), -1);
			handle_arg(&string, &properties, &args);
			if (string == NULL)
				return (va_end(args), -1);
		}
	}
	return (va_end(args), print_string(&string, fd));
}
