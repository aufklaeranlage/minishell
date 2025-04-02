/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listdel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@students.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:42:36 by abronner          #+#    #+#             */
/*   Updated: 2025/04/02 12:28:38 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_list.h"

void	ft_lstdelone(t_list *node, void (*del)(void *))
{
	if (!node)
		return ;
	(del)(node->content);
	free(node);
}

void	ft_listdelnext(t_list **node, void (*del)(void *))
{
	t_list	*tmp;

	if (!node || !*node)
		return ;
	tmp = (*node)->next;
	if (!tmp)
		return ;
	(*node)->next = tmp->next;
	del(tmp->content);
	free(tmp);
}

void	ft_listdelfirst(t_list **head, void (*del)(void *))
{
	t_list	*tmp;

	if (!head || !*head)
		return ;
	tmp = (*head)->next;
	del((*head)->content);
	free(*head);
	*head = tmp;
}

void	ft_lstclear(t_list **head, void (*del)(void *))
{
	t_list	*node;
	t_list	*tmp;

	if (!head || !*head)
		return ;
	node = *head;
	while (node)
	{
		tmp = node->next;
		(del)(node->content);
		free(node);
		node = tmp;
	}
	*head = NULL;
}
