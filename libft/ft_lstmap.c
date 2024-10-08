/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgebetsb <bgebetsb@students.42vienna.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:17:10 by bgebetsb          #+#    #+#             */
/*   Updated: 2024/04/04 18:42:48 by bgebetsb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static t_list	*new_lst(void *content, void *(*f)(void *), void (*del)(void *))
{
	void	*newcontent;
	t_list	*newlist;

	newcontent = f(content);
	newlist = ft_lstnew(newcontent);
	if (newlist == NULL)
	{
		del(newcontent);
		return (NULL);
	}
	return (newlist);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*cur;
	t_list	*cur_new;

	if (lst != NULL && f != NULL && del != NULL)
	{
		new = new_lst(lst->content, f, del);
		if (new == NULL)
			return (NULL);
		cur = lst->next;
		while (cur != NULL)
		{
			cur_new = new_lst(cur->content, f, del);
			if (cur_new == NULL)
			{
				ft_lstclear(&new, del);
				return (NULL);
			}
			ft_lstadd_back(&new, cur_new);
			cur = cur->next;
		}
		return (new);
	}
	return (NULL);
}
