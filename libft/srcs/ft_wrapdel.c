/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wrapdel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@students.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:45:36 by abronner          #+#    #+#             */
/*   Updated: 2025/06/11 15:54:01 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_list.h"

void	ft_wrapdelfirst(t_wrap *wrap, void (*del)(void *))
{
	t_list	*tmp;

	if (!wrap || !wrap->head)
		return ;
	tmp = wrap->head;
	if (wrap->head == wrap->tail)
		wrap->tail = NULL;
	wrap->head = tmp->next;
	(del)(tmp->content);
	free(tmp);
	--wrap->size;
}

void	ft_wrapdellast(t_wrap *wrap, void (*del)(void *))
{
	t_list	*tmp;

	if (!wrap || !wrap->head || !wrap->tail)
		return ;
	if (wrap->head == wrap->tail)
		wrap->tail = NULL;
	tmp = wrap->head;
	while (tmp->next != wrap->tail)
		tmp = tmp->next;
	if (tmp->next)
	{
		(del)(tmp->next->content);
		free(tmp->next);
		wrap->tail = tmp;
		tmp->next = NULL;
	}
	else
	{
		(del)(tmp->content);
		free(tmp);
		wrap->head = NULL;
	}
}

void	ft_wrapclear(t_wrap *wrap, void (*del)(void *))
{
	ft_lstclear(&(wrap->head), del);
	wrap->head = NULL;
	wrap->tail = NULL;
	wrap->size = 0;
	free(wrap);
}
