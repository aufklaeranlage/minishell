/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups_handle_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:55:34 by akuzmin           #+#    #+#             */
/*   Updated: 2025/05/23 10:05:41 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/tokenisation.h"

t_group	*handle_command_group(t_tokens *list, t_group *parrent, \
	size_t origin_i, size_t i)
{
	t_group		*group;
	t_tokens	*filtered;
	size_t		j;

	group = prepare_group(list, parrent, i, &j);
	if (!group)
		return (NULL);
	filtered = proc_cmd_tokens(group, list, i, j);
	if (!filtered)
		return (NULL);
	group->data = filtered;
	redirection(group, list, origin_i);
	setup_next_group(group, list, j, parrent);
	return (group);
}
