/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups_create_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:55:34 by akuzmin           #+#    #+#             */
/*   Updated: 2025/05/20 00:27:30 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/tokenisation.h"

void	free_redirection(t_token *red)
{
	size_t	i;

	if (!red)
		return ;
	i = 0;
	while (red[i].cont)
		free(red[i++].cont);
	free(red);
}

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
		if (list->data[j].type == O_BR)
			depth++;
		else if (list->data[j].type == C_BR)
			depth--;
		j++;
	}
	if (depth != 0)
		free(group);
	*j_out = j;
	return (group);
}
