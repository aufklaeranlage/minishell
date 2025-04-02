/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_list.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:16:59 by abronner          #+#    #+#             */
/*   Updated: 2025/04/02 12:28:22 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_LIST_H
# define LIBFT_LIST_H

# include <stdlib.h>

//	TYPEDEF

typedef struct s_list
{
	void			*content;
	size_t			size;
	struct s_list	*next;
}	t_list;

typedef struct s_wrap
{
	t_list	*head;
	t_list	*tail;
	size_t	size;
}			t_wrap;

//	LIST ADD

void		ft_lstadd_front(t_list **head, t_list *node);

void		ft_lstadd_back(t_list **head, t_list *node);

void		ft_lstinsert(t_list *node, t_list *pos);

//	LIST DEL

void		ft_lstdelone(t_list *node, void (*del)(void *));

void		ft_lstdelnext(t_list **node, void (*del)(void *));

void		ft_lstdelfirst(t_list **head, void (*del)(void *));

void		ft_lstclear(t_list **head, void (*del)(void *));

//	LIST UTILS

t_list		*ft_lstnew(void *data);

t_list		*ft_lstlast(t_list *node);

int			ft_lstsize(t_list *node);

//	LIST ITER

void		ft_lstiter(t_list *head, void (*f)(void *));

t_list		*ft_lstmap(t_list *head, void *(*f)(void *), void (*del)(void *));

//	WRAP ADD

void		ft_wrapadd_front(t_wrap *wrap, t_list *node);

void		ft_wrapadd_back(t_wrap *wrap, t_list *node);

void		ft_wrapinsert(t_wrap *wrap, t_list *node, t_list *pos);

//	WRAP DEL

void		ft_wrapclear(t_wrap *wrap, void (*del)(void *));

void		ft_wrapdelfirst(t_wrap *wrap, void (*del)(void *));

//	WRAP ITER

void		ft_wrapiter(t_wrap *wrap, void (*f)(void *));

t_wrap		*ft_wrapmap(t_wrap *wrap, void *(*f)(void *), void (*del)(void *));

#endif
