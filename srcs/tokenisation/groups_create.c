/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:55:34 by akuzmin           #+#    #+#             */
/*   Updated: 2025/05/20 23:25:42 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/tokenisation.h"

static size_t	skip_special_tokens(t_tokens *list, size_t i)
{
	while (i < list->size \
		&& (list->type[i] == AND || list->type[i] == OR \
			|| list->type[i] == PIPE || list->type[i] == C_BR))
		i++;
	while (i < list->size && list->type[i] >= RED_IN \
		&& list->type[i] <= ADD_OUT)
		i++;
	return (i);
}

static t_group	*handle_bracket_case(t_tokens *list, t_group *parrent, \
	size_t i, size_t *j)
{
	t_group	*group;

	group = handle_bracket_group(list, i, j);
	if (!group)
		return (NULL);
	if (!process_bracket_content(group, list, i, *j))
	{
		free(group);
		return (NULL);
	}
	group->parrent = parrent;
	return (group);
}

static void	setup_next_bracket_group(t_group *group, t_tokens *list, \
	size_t *j, t_group *parrent)
{
	if (*j < list->size && list->type[*j] == PIPE)
	{
		group->exec_type = PIPE;
		(*j)++;
	}
	if (*j < list->size)
		group->next = create_groups(list, parrent, *j, 0);
}

static int	is_valid_input(t_tokens *list, size_t i)
{
	if (!list || list->size == 0 || i >= list->size)
		return (0);
	return (1);
}

t_group	*create_groups(t_tokens *list, t_group *parrent, size_t i, size_t j)
{
	t_group	*group;

	if (!is_valid_input(list, i))
		return (NULL);
	i = skip_special_tokens(list, i);
	if (i >= list->size)
		return (NULL);
	if (list->type[i] == O_BR)
	{
		group = handle_bracket_case(list, parrent, i, &j);
		if (!group)
			return (NULL);
		setup_next_bracket_group(group, list, &j, parrent);
	}
	else
		group = handle_command_group(list, parrent, i);
	return (group);
}
