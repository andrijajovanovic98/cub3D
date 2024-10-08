/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgebetsb <bgebetsb@students.42vienna.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 09:47:21 by bgebetsb          #+#    #+#             */
/*   Updated: 2024/05/18 09:47:23 by bgebetsb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	string_clear(t_string **str)
{
	if (*str != NULL)
	{
		ft_lstclear(&((*str)->buffers), &strlist_delete_content);
		free(*str);
		*str = NULL;
	}
}

void	strlist_delete_content(void *content)
{
	t_strbuf	*c;

	c = (t_strbuf *)content;
	free(c->buf);
	free(c);
}

static size_t	max(size_t number1, size_t number2)
{
	if (number1 > number2)
		return (number1);
	else
		return (number2);
}

t_string	*string_append(t_string *str, char *new, size_t length)
{
	t_strbuf	*strbuf;
	t_list		*strlist;
	t_string	*string;

	strbuf = (t_strbuf *)ft_calloc(1, sizeof(t_strbuf));
	if (strbuf == NULL)
		return (string_clear(&str), free(new), NULL);
	strbuf->buf = new;
	strbuf->length = length;
	strlist = ft_lstnew(strbuf);
	if (strlist == NULL)
		return (free(strbuf->buf), free(strbuf), string_clear(&str), NULL);
	if (str != NULL)
	{
		ft_lstadd_front(&(str->buffers), strlist);
		str->total_length += length;
		str->max_length = max(str->max_length, length);
		return (str->items++, str);
	}
	string = (t_string *)ft_calloc(1, sizeof(t_string));
	if (string == NULL)
		return (free(strbuf->buf), free(strbuf), free(strlist), NULL);
	string->buffers = strlist;
	string->total_length = length;
	return (string->max_length = length, string->items = 1, string);
}

char	*string_get(t_string *str)
{
	char		*string;
	t_strbuf	*content;
	t_list		*tmp;
	size_t		i;
	size_t		j;

	if (str == NULL)
		return (NULL);
	string = (char *)ft_calloc(str->total_length + 1, sizeof(char));
	if (string == NULL)
		return (NULL);
	tmp = (t_list *)str->buffers;
	i = 0;
	while (tmp != NULL)
	{
		j = 0;
		content = (t_strbuf *)tmp->content;
		while (j < content->length)
			string[str->total_length - i++ - 1]
				= content->buf[content->length - j++ - 1];
		tmp = tmp->next;
	}
	return (string);
}
