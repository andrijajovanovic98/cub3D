/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgebetsb <bgebetsb@students.42vienna.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:56:21 by bgebetsb          #+#    #+#             */
/*   Updated: 2024/04/04 15:02:06 by bgebetsb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t	size;
	t_list	*cur;

	if (lst == NULL)
	{
		return (0);
	}
	size = 1;
	cur = lst;
	while (cur->next != NULL)
	{
		size++;
		cur = cur->next;
	}
	return (size);
}
