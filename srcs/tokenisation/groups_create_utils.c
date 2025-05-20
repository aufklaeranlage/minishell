/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups_create_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:55:34 by akuzmin           #+#    #+#             */
/*   Updated: 2025/05/20 23:25:47 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/tokenisation.h"

t_group	*handle_bracket_group(t_tokens *list, size_t i, size_t *j_out)
{
	t_group		*group;
	size_t		j;
	size_t		depth;

	depth = 1;
	group = malloc(sizeof(t_group));
	if (!group)
		return (NULL);
	group->next = NULL;
	group->red = NULL;
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
		free(group);
	*j_out = j;
	return (group);
}
