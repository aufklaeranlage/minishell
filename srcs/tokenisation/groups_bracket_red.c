/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups_bracket_red.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 08:35:17 by akuzmin           #+#    #+#             */
/*   Updated: 2025/05/20 23:35:28 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/tokenisation.h"

int	handle_bracket_redirection(t_group *group, t_tokens *list, size_t j)
{
	if (j < list->size && list->type[j] >= RED_IN \
		&& list->type[j] <= ADD_OUT)
	{
		group->red = malloc(sizeof(t_tokens));
		if (!group->red)
			return (0);
		group->red->size = 1;
		group->red->type = malloc(sizeof(int));
		group->red->content = malloc(sizeof(char *) * 2);
		if (!group->red->type || !group->red->content)
		{
			del_tokens(group->red);
			group->red = NULL;
			return (0);
		}
		group->red->type[0] = list->type[j];
		group->red->content[0] = ft_strdup(list->content[j]);
		group->red->content[1] = NULL;
		if (!group->red->content[0])
		{
			group->red = del_tokens(group->red);
			return (0);
		}
	}
	return (1);
}
