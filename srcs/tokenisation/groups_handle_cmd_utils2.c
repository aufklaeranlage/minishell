/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups_handle_cmd_utils2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:55:34 by akuzmin           #+#    #+#             */
/*   Updated: 2025/05/19 23:55:53 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/tokenisation.h"

int	copy_valid_tokens(t_tokens *filtered, t_tokens *sub, t_group *group)
{
	size_t	k;

	k = 0;
	while (k < sub->size)
	{
		if (sub->data[k].type < RED_IN || sub->data[k].type > ADD_OUT)
		{
			filtered->data[filtered->size].type = sub->data[k].type;
			filtered->data[filtered->size].cont = ft_strdup(sub->data[k].cont);
			if (!filtered->data[filtered->size].cont)
			{
				cleanup_filtered_tokens(filtered, sub, group);
				return (0);
			}
			filtered->size++;
		}
		k++;
	}
	return (1);
}

void	cleanup_filtered_tokens(t_tokens *fltrd, t_tokens *sub, t_group *group)
{
	size_t	m;

	m = 0;
	while (m < fltrd->size)
	{
		free(fltrd->data[m].cont);
		m++;
	}
	free(fltrd->data);
	free(fltrd);
	free(sub->data);
	free(sub);
	free_redirection(group->red);
	free(group);
}

void	setup_next_group(t_group *group, t_tokens *list, size_t j, t_group *pnt)
{
	if (j < list->size)
	{
		if (list->data[j].type == AND || list->data[j].type == OR \
			|| list->data[j].type == PIPE)
			j++;
		if (j < list->size)
			group->next = create_groups(list, pnt, j, 0);
	}
}

t_group	*prepare_group(t_tokens *list, t_group *pnt, size_t i, size_t *j_out)
{
	t_group	*group;
	size_t	j;

	if (!is_valid_cmd_position(list, i))
		return (NULL);
	group = init_cmd_group(list, pnt, i);
	if (!group)
		return (NULL);
	j = delimiter(&group->exec_type, list, i);
	if (j == 0)
		j = list->size;
	*j_out = j;
	return (group);
}

t_tokens	*proc_cmd_tokens(t_group *group, t_tokens *list, size_t i, size_t j)
{
	t_tokens	*sub;
	t_tokens	*filtered;
	size_t		valid_count;

	sub = get_command_tokens(list, i, j);
	if (!sub)
	{
		free_redirection(group->red);
		free(group);
		return (NULL);
	}
	valid_count = count_valid_tokens(sub);
	filtered = filter_tokens(valid_count, group, sub);
	if (!filtered)
		return (NULL);
	if (!copy_valid_tokens(filtered, sub, group))
		return (NULL);
	free(sub->data);
	free(sub);
	return (filtered);
}
