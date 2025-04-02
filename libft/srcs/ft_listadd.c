/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listadd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@students.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:42:32 by abronner          #+#    #+#             */
/*   Updated: 2025/04/02 12:27:27 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_list.h"

void	ft_lstadd_front(t_list **head, t_list *node)
{
	if (!head || !node)
		return ;
	node->next = *head;
	*head = node;
}

void	ft_lstadd_back(t_list **head, t_list *node)
{
	t_list	*tmp;

	if (!head || !node)
		return ;
	tmp = ft_lstlast(*head);
	if (!tmp)
		*head = node;
	else
		tmp->next = node;
}

void	ft_lstinsert(t_list *node, t_list *pos)
{
	if (!node || !pos)
		return ;
	node->next = pos->next;
	pos->next = node;
}
