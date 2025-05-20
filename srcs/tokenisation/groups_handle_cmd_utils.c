/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups_handle_cmd_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:55:34 by akuzmin           #+#    #+#             */
/*   Updated: 2025/05/19 23:40:49 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/tokenisation.h"

int	is_valid_cmd_position(t_tokens *list, size_t i)
{
	size_t	j;

	if (i >= list->size)
		return (0);
	j = i;
	while (j < list->size && list->data[j].type != PIPE \
		&& list->data[j].type != AND && list->data[j].type != OR \
		&& list->data[j].type != C_BR)
	{
		j++;
	}
	if (j == i)
		return (0);
	return (1);
}

t_group	*init_cmd_group(t_tokens *list, t_group *parrent, size_t i)
{
	t_group	*group;
	size_t	j;

	group = malloc(sizeof(t_group));
	if (!group)
		return (NULL);
	group->next = NULL;
	group->red = NULL;
	group->parrent = parrent;
	group->data_type = CMD;
	group->data = NULL;
	group->exec_type = 0;
	j = delimiter(&group->exec_type, list, i);
	if (j == 0)
		j = list->size;
	redirection(group, list, i);
	return (group);
}

t_tokens	*get_command_tokens(t_tokens *list, size_t i, size_t j)
{
	t_tokens	*sub;

	sub = subtoken(list, i, j);
	return (sub);
}

size_t	count_valid_tokens(t_tokens *sub)
{
	size_t	valid_count;
	size_t	k;

	valid_count = 0;
	k = 0;
	while (k < sub->size)
	{
		if (sub->data[k].type < RED_IN || sub->data[k].type > ADD_OUT)
			valid_count++;
		k++;
	}
	return (valid_count);
}

t_tokens	*filter_tokens(size_t valid_count, t_group *group, t_tokens *sub)
{
	t_tokens	*filtered;

	filtered = malloc(sizeof(t_tokens));
	if (!filtered)
	{
		free(sub->data);
		free(sub);
		free_redirection(group->red);
		free(group);
		return (NULL);
	}
	if (valid_count <= 0)
		valid_count = 1;
	filtered->data = malloc(sizeof(t_token) * valid_count);
	if (!filtered->data)
	{
		free(filtered);
		free(sub->data);
		free(sub);
		free_redirection(group->red);
		free(group);
		return (NULL);
	}
	filtered->size = 0;
	return (filtered);
}
