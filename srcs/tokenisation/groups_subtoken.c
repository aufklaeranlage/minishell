/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups_subtoken.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:44:00 by akuzmin           #+#    #+#             */
/*   Updated: 2025/06/23 23:34:40 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/tokenisation.h"

static t_tokens	*alloc_empty_token(void)
{
	t_tokens	*cmd;

	cmd = malloc(sizeof(t_tokens));
	if (!cmd)
		return (NULL);
	cmd->size = 0;
	cmd->type = malloc(sizeof(int));
	cmd->content = malloc(sizeof(char *));
	if (!cmd->type || !cmd->content)
		return (del_tokens(cmd));
	cmd->content[0] = NULL;
	return (cmd);
}

static void	fill_cmd_subtoken(t_tokens	*cmd, t_tokens *list, \
	size_t start, size_t end)
{
	size_t	i;

	i = 0;
	while (i < end - start)
	{
		cmd->type[i] = list->type[start + i];
		cmd->content[i] = ft_strdup(list->content[start + i]);
		if (!cmd->content[i])
		{
			del_tokens(cmd);
			return ;
		}
		i++;
	}
	cmd->content[i] = NULL;
}

t_tokens	*subtoken(t_tokens *list, size_t start, size_t end)
{
	t_tokens	*cmd;
	size_t		count;

	if (start >= list->size || end > list->size || start >= end)
		return (alloc_empty_token());
	count = end - start;
	cmd = malloc(sizeof(t_tokens));
	if (!cmd)
		return (NULL);
	cmd->size = count;
	cmd->type = malloc(sizeof(int) * count);
	cmd->content = malloc(sizeof(char *) * (count + 1));
	if (!cmd->type || !cmd->content)
		return (del_tokens(cmd));
	fill_cmd_subtoken(cmd, list, start, end);
	return (cmd);
}
