/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgebetsb <bgebetsb@students.42vienna.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:37:41 by bgebetsb          #+#    #+#             */
/*   Updated: 2024/04/04 17:58:49 by bgebetsb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*cur;

	if (lst != NULL && del != NULL)
	{
		cur = *lst;
		while (cur != NULL)
		{
			tmp = cur->next;
			del(cur->content);
			free(cur);
			cur = tmp;
		}
		*lst = 0;
	}
}
