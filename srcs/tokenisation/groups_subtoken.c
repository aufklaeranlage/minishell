/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtoken.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:44:00 by akuzmin           #+#    #+#             */
/*   Updated: 2025/05/19 23:03:56 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/tokenisation.h"

static t_tokens	*alloc_empty_token(void)
{
	t_tokens	*cmd;

	cmd = malloc(sizeof(t_tokens));
	if (!cmd)
		return (NULL);
	cmd->data = malloc(sizeof(t_token));
	if (!cmd->data)
		return (del_tokens(cmd));
	cmd->size = 0;
	return (cmd);
}

t_tokens	*subtoken(t_tokens *list, size_t start, size_t end)
{
	t_tokens	*cmd;
	size_t		count;
	size_t		i;

	if (start >= list->size || end > list->size || start >= end)
		return (alloc_empty_token());
	count = end - start;
	cmd = malloc(sizeof(t_tokens));
	if (!cmd)
		return (NULL);
	cmd->data = malloc(sizeof(t_token) * count);
	if (!cmd->data)
		return (del_tokens(cmd));
	cmd->size = count;
	i = 0;
	while (i < count)
	{
		cmd->data[i].type = list->data[start + i].type;
		cmd->data[i].cont = ft_strdup(list->data[start + i].cont);
		if (!cmd->data[i].cont)
			return (del_tokens(cmd));
		i++;
	}
	return (cmd);
}
