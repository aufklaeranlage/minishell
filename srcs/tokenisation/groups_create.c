/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:55:34 by akuzmin           #+#    #+#             */
/*   Updated: 2025/06/17 11:35:10 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/tokenisation.h"

size_t	skip_special_tokens(t_tokens *list, size_t i)
{
	if (i < list->size \
		&& (list->type[i] == AND || list->type[i] == OR \
			|| list->type[i] == PIPE || list->type[i] == C_BR \
			|| list->type[i] == SMCLN))
		i++;
	if (i < list->size && list->type[i] >= RED_IN \
		&& list->type[i] <= ADD_OUT)
		i++;
	return (i);
}

static t_group	*handle_bracket_case(t_tokens *list, t_group *parrent, \
	size_t i, size_t *j)
{
	t_group	*group;

	group = handle_bracket_group(list, skip_special_tokens(list, i), j);
	if (!group)
		return (NULL);
	if (!process_bracket_content(group, list, i, j))
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

t_group *create_group_of_type(int type, t_group *parent)
{
    t_group *group;

    group = malloc(sizeof(t_group));
    if (!group)
        return (NULL);
    group->data_type = type;
    group->data = NULL;
    group->exec_type = 0;
    group->next = NULL;
    group->parrent = parent;
    
    return (group);
}

/**
 * @brief Recursively frees a group structure and all its children.
 *
 * This function handles the complete cleanup of a group structure:
 * - Frees any data associated with the group based on data_type
 * - Recursively frees any next group in the chain
 * - Frees any heredoc EOF string if present
 * - Finally frees the group structure itself
 *
 * @param group The group structure to free
 */
void free_group_recursive(t_group *group)
{
    if (!group)
        return;

    if (group->next)
        free_group_recursive(group->next);

    if (group->data)
    {
        if (group->data_type == CMD)
        {
            del_tokens((t_tokens *)group->data);
        }
        else if (group->data_type == SHELL || group->data_type == PIPELINE)
        {
            free_group_recursive((t_group *)group->data);
        }
    }
    free(group);
}

t_group	*create_groups(t_tokens *list, t_group *parent, size_t i, size_t j)
{
	t_group	*group;
	size_t	origin_i;

	if (!is_valid_input(list, i))
		return (NULL);
	origin_i = i;
	i = skip_special_tokens(list, i);
	if (i >= list->size)
		return (NULL);
	if (list->type[i] == O_BR)
	{
		group = handle_bracket_case(list, parent, origin_i, &j);
		if (!group)
			return (NULL);
		setup_next_bracket_group(group, list, &j, parent);
	}
	else
		group = handle_command_group(list, parent, origin_i, i);
	return (group);
}