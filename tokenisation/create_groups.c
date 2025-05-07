/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_groups.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:55:34 by akuzmin           #+#    #+#             */
/*   Updated: 2025/05/07 15:33:11 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenisation.h"

static t_group	*handle_bracket_group(t_token *list, size_t i, size_t *j_out)
{
	t_group		*group;
	size_t		j;
	size_t		depth;

	depth = 1;
	group = malloc(sizeof(t_group));
	if (!group)
		return (NULL);
	group->next = NULL;
	j = i + 1;
	while (j < list->size && depth > 0)
	{
		if (list->type[j] == O_BR)
			depth++;
		else if (list->type[j] == C_BR)
			depth--;
		j++;
	}
	if (depth != 0)
	{
		free(group);
		return (NULL);
	}
	*j_out = j;
	return (group);
}

static int	process_bracket_content(t_group *group, t_token *list, \
	size_t i, size_t j)
{
	t_token	*sub;

	sub = subtoken(list, i + 1, j - 1);
	if (!sub)
		return (0);
	group->data_type = GROUP;
	group->data = create_groups(sub, 0, 0);
	if (!group->data)
	{
		free(sub);
		return (0);
	}
	free(sub);
	return (1);
}

static t_group	*handle_command_group(t_token *list, size_t i)
{
	t_group	*group;
	size_t	j;

	group = malloc(sizeof(t_group));
	if (!group)
		return (NULL);
	group->next = NULL;
	j = delimiter(&group->exec_type, list, i);
	if (j == 0)
		j = list->size;
	group->data = subtoken(list, i, j);
	group->data_type = CMD;
	if (j < list->size)
		group->next = create_groups(subtoken(list, j + 1, list->size), 0, 0);
	return (group);
}

/**
 * As inicialisation need to past 0 to i and j
 */
t_group	*create_groups(t_token *list, size_t i, size_t j)
{
	t_group	*group;

	if (list->size == 0)
		return (NULL);
	if (list->type[i] == PIPE || list->type[i] == OR || list->type[i] == AND)
	{
		group = malloc(sizeof(t_group));
		if (!group)
			return (NULL);
		group->next = NULL;
		group->exec_type = list->type[i++];
	}
	if (list->type[i] == O_BR)
	{
		group = handle_bracket_group(list, i, &j);
		if (!group || !process_bracket_content(group, list, i, j))
			return (NULL);
		if (j < list->size)
			group->next = create_groups(subtoken(list, j, list->size), 0, 0);
	}
	else
		group = handle_command_group(list, i);
	return (group);
}
