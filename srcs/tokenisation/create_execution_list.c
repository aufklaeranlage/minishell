/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_execution_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:22:19 by akuzmin           #+#    #+#             */
/*   Updated: 2025/05/21 00:09:08 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/tokenisation.h"

void	*del_tokens(t_tokens *out)
{
	size_t	i;

	i = 0;
	if (!out)
		return (NULL);
	if (out->content)
	{
		while (i < out->size && out->content[i])
			free(out->content[i++]);
		free(out->content);
	}
	if (out->type)
		free(out->type);
	free(out);
	return (NULL);
}

static int	process_tokens(t_tokens **out, t_wrap *list, char **env)
{
	*out = malloc(sizeof(t_tokens));
	if (!*out)
		return (1);
	(*out)->size = list->size;
	(*out)->type = malloc(sizeof(int) * list->size);
	(*out)->content = malloc(sizeof(char *) * (list->size + 1));
	if (!(*out)->type || !(*out)->content)
	{
		del_tokens(*out);
		*out = NULL;
		return (1);
	}
	(*out)->content[list->size] = NULL;
	lst_to_tokens(*out, list, env);
	return (0);
}

static int	wrap_operations(t_tokens **out, char *str, char **env)
{
	t_wrap		*list;

	list = convert_str(str);
	if (!list)
		return (1);
	if (process_tokens(out, list, env))
	{
		ft_wrapclear(list, free);
		return (1);
	}
	ft_wrapclear(list, free);
	return (0);
}

int	create_execution_list(t_group *group, char *str, char **env)
{
	t_tokens	*tokens;
	t_group		*parsed_group;

	if (!group)
		return (1);
	tokens = NULL;
	if (wrap_operations(&tokens, str, env))
		return (1);
	parsed_group = create_groups(tokens, NULL, 0, 0);
	del_tokens(tokens);
	if (!parsed_group)
		return (1);
	group->data_type = parsed_group->data_type;
	group->exec_type = parsed_group->exec_type;
	group->red = parsed_group->red;
	group->data = parsed_group->data;
	group->next = parsed_group->next;
	group->parrent = parsed_group->parrent;
	free(parsed_group);
	// CHECK FOR  ANY VIOLATIONS IN USAGE
	return (0);
}
