/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:44:00 by akuzmin           #+#    #+#             */
/*   Updated: 2025/05/23 11:25:50 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/tokenisation.h"

static int	count_redir_tokens(t_tokens *list, size_t i)
{
	size_t	count;

	count = 0;
	while (i < list->size && list->type[i] != PIPE \
		&& list->type[i] != AND && list->type[i] != OR \
		&& list->type[i] != C_BR)
	{
		if (list->type[i] >= RED_IN && list->type[i] <= ADD_OUT)
			count++;
		i++;
	}
	return (count);
}

static t_tokens	*create_redir_tokens(int count)
{
	t_tokens	*red;

	if (count == 0)
		return (NULL);
	red = malloc(sizeof(t_tokens));
	if (!red)
		return (NULL);
	red->size = count;
	red->type = malloc(sizeof(int) * count);
	red->content = malloc(sizeof(char *) * (count + 1));
	if (!red->type || !red->content)
		return (del_tokens(red));
	red->content[count] = NULL;
	return (red);
}

static int	copy_redirections(t_tokens *dest, t_tokens *list, size_t i)
{
	size_t	iter;

	iter = 0;
	while (i < list->size && list->type[i] != PIPE \
		&& list->type[i] != AND && list->type[i] != OR \
		&& list->type[i] != C_BR)
	{
		if (list->type[i] >= RED_IN && list->type[i] <= ADD_OUT)
		{
			dest->type[iter] = list->type[i];
			dest->content[iter] = ft_strdup(list->content[i]);
			if (!dest->content[iter])
				return (-1);
			iter++;
		}
		i++;
	}
	return (0);
}

void	redirection(t_group *group, t_tokens *list, size_t i)
{
	int			count;
	t_tokens	*red;

	count = count_redir_tokens(list, i);
	if (count == 0)
	{
		group->red = NULL;
		return ;
	}
	red = create_redir_tokens(count);
	if (!red || copy_redirections(red, list, i) < 0)
	{
		del_tokens(red);
		group->red = NULL;
		return ;
	}
	if (!group->red)
		group->red = red;
	else
		append_tokens(&(group->red), red);
}
