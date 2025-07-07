/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups_handle_cmd_utils2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:55:34 by akuzmin           #+#    #+#             */
/*   Updated: 2025/06/24 17:30:24 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/tokenisation.h"

int	copy_valid_tokens(t_tokens *filtered, t_tokens *sub, t_group *group)
{
	size_t	k;

	k = 0;
	while (k < sub->size)
	{
		if (sub->type[k] < RED_IN || sub->type[k] > ADD_OUT)
		{
			filtered->type[filtered->size] = sub->type[k];
			filtered->content[filtered->size] = ft_strdup(sub->content[k]);
			if (!filtered->content[filtered->size])
			{
				cleanup_filtered_tokens(filtered, sub, group);
				return (0);
			}
			filtered->size++;
		}
		k++;
	}
	filtered->content[filtered->size] = NULL;
	return (1);
}

void	cleanup_filtered_tokens(t_tokens *fltrd, t_tokens *sub, t_group *group)
{
	token_free(fltrd);
	token_free(sub);
	token_free(group->red);
	group_free(group);
}

void	setup_next_group(t_group *group, t_tokens *list, size_t j, t_group *pnt)
{
	if (j < list->size)
	{
		if (list->type[j] == AND || list->type[j] == OR \
			|| list->type[j] == PIPE)
			j++;
		if (j < list->size)
			group->next = create_groups(list, pnt, j, 0);
	}
}

t_group	*prepare_group(t_tokens *list, t_group *pnt, size_t i, size_t *j_out)
{
	t_group	*group;
	size_t	j;

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
		return (token_free(group->red), group_free(group), NULL);
	valid_count = count_valid_tokens(sub);
	filtered = filter_tokens(valid_count, group, sub);
	if (!filtered)
		return (NULL);
	if (!copy_valid_tokens(filtered, sub, group))
		return (NULL);
	return (token_free(sub), filtered);
}
