/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wrapadd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@students.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:44:00 by abronner          #+#    #+#             */
/*   Updated: 2025/04/02 12:29:06 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_list.h"

void	ft_wrapadd_front(t_wrap *wrap, t_list *node)
{
	if (!wrap || !node)
		return ;
	node->next = wrap->head;
	wrap->head = node;
	++wrap->size;
}

void	ft_wrapadd_back(t_wrap *wrap, t_list *node)
{
	if (!wrap || !node)
		return ;
	if (wrap->tail)
	{
		wrap->tail->next = node;
		wrap->tail = node;
	}
	else
	{
		wrap->tail = node;
		wrap->head = node;
	}
	++wrap->size;
}

void	ft_wrapinsert(t_wrap *wrap, t_list *node, t_list *pos)
{
	if (!wrap || !node || !pos)
		return ;
	node->next = pos->next;
	pos->next = node;
	++wrap->size;
}
