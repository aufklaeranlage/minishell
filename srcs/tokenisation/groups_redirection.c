/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:44:00 by akuzmin           #+#    #+#             */
/*   Updated: 2025/05/19 23:03:56 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/tokenisation.h"

static int	count_redir_tokens(t_tokens *list, size_t i)
{
	size_t	count;

	count = 0;
	while (i < list->size && list->data[i].type != PIPE \
		&& list->data[i].type != AND && list->data[i].type != OR \
		&& list->data[i].type != C_BR)
	{
		if (list->data[i].type >= RED_IN && list->data[i].type <= ADD_OUT)
			count++;
		i++;
	}
	return (count);
}

static int	copy_redirections(t_token *dest, t_tokens *list, size_t i)
{
	size_t	iter;

	iter = 0;
	while (i < list->size && list->data[i].type != PIPE \
		&& list->data[i].type != AND && list->data[i].type != OR \
		&& list->data[i].type != C_BR)
	{
		if (list->data[i].type >= RED_IN && list->data[i].type <= ADD_OUT)
		{
			dest[iter].type = list->data[i].type;
			dest[iter].cont = ft_strdup(list->data[i].cont);
			if (!dest[iter].cont)
				return (-1);
			iter++;
		}
		i++;
	}
	dest[iter].cont = NULL;
	return (0);
}

void	redirection(t_group *group, t_tokens *list, size_t i)
{
	int	count;

	count = count_redir_tokens(list, i);
	if (count == 0)
	{
		group->red = NULL;
		return ;
	}
	group->red = malloc(sizeof(t_token) * (count + 1));
	if (!group->red || copy_redirections(group->red, list, i) < 0)
	{
		free(group->red);
		group->red = NULL;
	}
}
