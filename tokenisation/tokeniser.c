/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:55:34 by akuzmin           #+#    #+#             */
/*   Updated: 2025/05/07 15:32:21 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenisation.h"

static int	set_type(char *tmp, char **env)
{
	if (specifier_one(tmp))
		return (specifier_one(tmp));
	else if (specifier_two(tmp))
		return (specifier_two(tmp));
	else if (cmd_specifier(tmp))
		return (cmd_specifier(tmp));
	else if (minishell_getexec(tmp, env))
		return (STD_CMD);
	else if (is_falg(tmp))
		return (FLAG);
	else
		return (TEXT);
}

size_t	delimiter(int *d_type, t_token	*list, size_t i)
{
	while (i < list->size)
	{
		if (list->type[i] == PIPE || list->type[i] == OR \
			|| list->type[i] == AND)
		{
			*d_type = list->type[i];
			return (i);
		}
		i++;
	}
	return (0);
}

t_token	*subtoken(t_token *list, size_t start, size_t end)
{
	t_token		*cmd;
	size_t		x;

	cmd = malloc(sizeof(t_token));
	cmd->content = malloc(sizeof(char *) * (end - start));
	cmd->type = malloc(sizeof(int) * (end - start));
	cmd->size = end - start;
	x = 0;
	while (start + x < end)
	{
		cmd->content[x] = ft_strdup(list->content[start + x]);
		cmd->type[x] = list->type[start + x];
		x++;
	}
	return (cmd);
}

static void	lst_to_tokens(t_token *out, t_wrap *list, char **env)
{
	size_t		i;
	char		*tmp;
	t_list		*current;

	i = 0;
	current = list->head;
	while (i < list->size && current)
	{
		tmp = ft_strdup((char *)current->content);
		if (!tmp)
			return ;
		out->type[i] = set_type(tmp, env);
		if (out->type[i] == STR || out->type[i] == EXPAND_STR)
		{
			out->content[i] = ft_substr(tmp, 1, ft_strlen(tmp) - 2);
			if (!out->content[i])
				out->content[i] = ft_strdup("");
		}
		else
			out->content[i] = ft_strdup(tmp);
		free(tmp);
		current = current->next;
		i++;
	}
}

t_group	*create_execution_list(char *str, char **env)
{
	t_token	*out;
	t_wrap	*list;
	t_group	*group;

	list = convert_str(str);
	if (!list)
		return (NULL);
	out = malloc(sizeof(t_token));
	if (!out)
		return (NULL);
	out->content = malloc(sizeof(char *) * list->size);
	out->type = malloc(sizeof(int) * list->size);
	out->size = list->size;
	if (!out->content || !out->type)
		return (NULL);
	lst_to_tokens(out, list, env);
	ft_wrapclear(list, free);
	group = create_groups(out, 0, 0);
	free(out);
	return (group);
}
