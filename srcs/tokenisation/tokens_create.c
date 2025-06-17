/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:55:34 by akuzmin           #+#    #+#             */
/*   Updated: 2025/06/13 11:05:53 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenisation.h"

static int	process_redirect(t_tokens *out, size_t i, t_list **curr, char *tmp)
{
	if (!(*curr)->next)
	{
		free(tmp);
		out->content[i] = ft_strdup("");
		if (!out->content[i])
			return (1);
		return (0);
	}
	*curr = (*curr)->next;
	out->content[i] = ft_strdup((char *)(*curr)->content);
	if (!out->content[i])
	{
		free(tmp);
		return (1);
	}
	return (0);
}

static int	process_string(t_tokens *out, size_t i, char *tmp)
{
	if (ft_strlen(tmp) < 2)
		out->content[i] = ft_strdup("");
	else
		out->content[i] = ft_substr(tmp, 1, ft_strlen(tmp) - 2);
	if (!out->content[i])
	{
		free(tmp);
		out->content[i] = ft_strdup("");
		if (!out->content[i])
			return (1);
	}
	return (0);
}

static int	process_regular(t_tokens *out, size_t i, char *tmp)
{
	out->content[i] = ft_strdup(tmp);
	if (!out->content[i])
	{
		free(tmp);
		return (1);
	}
	if (ft_strchr(tmp, '=') != NULL)
		out->type[i] = ASSIGNMENT;
	return (0);
}

static int	process_token(t_tokens *out, size_t i, t_list **curr, char **env)
{
	char	*tmp;
	int		result;

	tmp = ft_strdup((char *)(*curr)->content);
	if (!tmp)
		return (1);
	out->type[i] = set_type(tmp, env);
	result = 0;
	if (tmp[0] == '.' && tmp[1] == '/' \
		&& access(tmp, F_OK | X_OK) == 0)
		out->type[i] = STD_CMD;
	if (out->type[i] >= RED_IN && out->type[i] <= ADD_OUT)
	{
		result = process_redirect(out, i, curr, tmp);
		*curr = (*curr)->next;
	}
	else if (out->type[i] == STR || out->type[i] == EXPAND_STR)
		result = process_string(out, i, tmp);
	else if (out->type[i] == STD_CMD && access(tmp, F_OK | X_OK) == 0 \
			&& ft_strchr(tmp, '/') && ft_strlen(tmp) + tmp - 1 != ft_strchr(tmp, '/'))
		result = process_regular(out, i, tmp);
	else
		result = process_regular(out, i, tmp);
	free(tmp);
	return (result);
}

void	lst_to_tokens(t_tokens *out, t_wrap *list, char **env)
{
	size_t	i;
	t_list	*curr;
	int		redir_flag;

	i = 0;
	curr = list->head;
	while (i < list->size && curr && i < out->size)
	{
		redir_flag = 0;
		if (curr && curr->content)
		{
			if (process_token(out, i, &curr, env))
				return ;
			if (out->type[i] >= RED_IN && out->type[i] <= ADD_OUT)
				redir_flag = 1;
		}
		if (!redir_flag)
			curr = curr->next;
		i++;
	}
	out->size = i;
	out->content[i] = NULL;
}
