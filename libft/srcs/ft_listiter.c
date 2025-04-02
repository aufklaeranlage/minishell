/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listiter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@students.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:42:40 by abronner          #+#    #+#             */
/*   Updated: 2025/04/02 12:28:52 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_list.h"

void	ft_lstiter(t_list *head, void (*f)(void *))
{
	t_list	*node;

	while (head)
	{
		node = head->next;
		(f)(head->content);
		head = node;
	}
}

t_list	*ft_lstmap(t_list *head, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newhead;
	t_list	*newnode;
	t_list	*tmp;
	void	*newcont;

	newhead = NULL;
	tmp = NULL;
	while (head)
	{
		newnode = ft_lstnew(NULL);
		newcont = (f)(head->content);
		if (!newhead)
			newhead = newnode;
		ft_lstadd_back(&tmp, newnode);
		if (!newnode || !newcont)
			return (ft_lstclear(&newhead, del), (del)(newcont), NULL);
		newnode->content = newcont;
		if (tmp != newnode)
			tmp = tmp->next;
		head = head->next;
	}
	return (newhead);
}
