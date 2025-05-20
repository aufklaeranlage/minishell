/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups_bracket_red.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 08:35:17 by akuzmin           #+#    #+#             */
/*   Updated: 2025/05/20 00:22:29 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/tokenisation.h"

int	handle_bracket_redirection(t_group *group, t_tokens *list, size_t j)
{
	if (j < list->size && list->data[j].type >= RED_IN \
		&& list->data[j].type <= ADD_OUT)
	{
		group->red = malloc(sizeof(t_token) * 2);
		if (!group->red)
			return (0);
		group->red[0].type = list->data[j].type;
		group->red[0].cont = ft_strdup(list->data[j].cont);
		if (!group->red[0].cont)
		{
			free(group->red);
			group->red = NULL;
			return (0);
		}
		group->red[1].cont = NULL;
	}
	return (1);
}
