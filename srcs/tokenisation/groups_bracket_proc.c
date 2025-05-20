/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups_bracket_proc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 08:30:12 by akuzmin           #+#    #+#             */
/*   Updated: 2025/05/20 23:25:55 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/tokenisation.h"

static int	set_connection_type(t_group *group, t_tokens *list, size_t j)
{
	if (j < list->size)
	{
		if (list->type[j] == PIPE)
			group->exec_type = PIPE;
		else if (list->type[j] == OR)
			group->exec_type = OR;
		else if (list->type[j] == AND)
			group->exec_type = AND;
		else
			group->exec_type = 0;
	}
	else
		group->exec_type = 0;
	return (1);
}

static int	create_bracket_content(t_group *group, t_tokens *sub)
{
	if (sub && sub->size > 0)
	{
		group->data = create_groups(sub, group, 0, 0);
		if (!group->data)
			return (0);
	}
	else
		group->data = NULL;
	return (1);
}

int	process_bracket_content(t_group *group, t_tokens *list, size_t i, size_t j)
{
	t_tokens	*sub;
	int			success;

	sub = subtoken(list, i + 1, j - 1);
	if (!sub)
		return (0);
	group->data_type = GROUP;
	set_connection_type(group, list, j);
	success = create_bracket_content(group, sub);
	del_tokens(sub);
	return (success);
}
