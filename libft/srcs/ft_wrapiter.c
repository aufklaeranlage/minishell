/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wrapiter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@students.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:45:41 by abronner          #+#    #+#             */
/*   Updated: 2025/04/02 12:29:20 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_list.h"

void	ft_wrapiter(t_wrap *wrap, void (*f)(void *))
{
	ft_lstiter(wrap->head, f);
}

t_wrap	*ft_wrapmap(t_wrap *wrap, void *(*f)(void *), void (*del)(void *))
{
	t_wrap	*newwrap;

	if (!wrap)
		return (NULL);
	newwrap = malloc(sizeof(*newwrap));
	if (!newwrap)
		return (NULL);
	newwrap->head = ft_lstmap(wrap->head, f, del);
	if (!newwrap->head)
		return (NULL);
	newwrap->tail = ft_lstlast(newwrap->head);
	newwrap->size = wrap->size;
	return (newwrap);
}
