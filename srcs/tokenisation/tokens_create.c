/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:55:34 by akuzmin           #+#    #+#             */
/*   Updated: 2025/05/19 23:16:49 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/tokenisation.h"

static int	process_redirect(t_tokens *out, size_t i, t_list **curr, char *tmp)
{
	if (!(*curr)->next)
	{
		free(tmp);
		out->data[i].cont = ft_strdup("");
		if (!out->data[i].cont)
			return (1);
		return (0);
	}
	*curr = (*curr)->next;
	out->data[i].cont = ft_strdup((char *)(*curr)->content);
	if (!out->data[i].cont)
	{
		free(tmp);
		return (1);
	}
	return (0);
}

static int	process_string(t_tokens *out, size_t i, char *tmp)
{
	if (ft_strlen(tmp) < 2)
		out->data[i].cont = ft_strdup("");
	else
		out->data[i].cont = ft_substr(tmp, 1, ft_strlen(tmp) - 2);
	if (!out->data[i].cont)
	{
		free(tmp);
		out->data[i].cont = ft_strdup("");
		if (!out->data[i].cont)
			return (1);
	}
	return (0);
}

static int	process_regular(t_tokens *out, size_t i, char *tmp)
{
	out->data[i].cont = ft_strdup(tmp);
	if (!out->data[i].cont)
	{
		free(tmp);
		return (1);
	}
	return (0);
}

static int	process_token(t_tokens *out, size_t i, t_list **curr, char **env)
{
	char	*tmp;
	int		result;

	tmp = ft_strdup((char *)(*curr)->content);
	if (!tmp)
		return (1);
	out->data[i].type = set_type(tmp, env);
	result = 0;
	if (out->data[i].type >= RED_IN && out->data[i].type <= ADD_OUT)
		result = process_redirect(out, i, curr, tmp);
	else if (out->data[i].type == STR || out->data[i].type == EXPAND_STR)
		result = process_string(out, i, tmp);
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
			if (out->data[i].type >= RED_IN && out->data[i].type <= ADD_OUT)
				redir_flag = 1;
			if (process_token(out, i, &curr, env))
				return ;
		}
		if (!redir_flag)
			curr = curr->next;
		i++;
	}
	out->size = i;
}
/*
void	lst_to_tokens(t_tokens *out, t_wrap *list, char **env)
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
		out->data[i].type = set_type(tmp, env);
		if (out->data[i].type >= RED_IN && out->data[i].type <= ADD_OUT)
		{
			if (!current->next)
			{
				free(tmp);
				out->data[i].cont = ft_strdup("");
				if (!out->data[i].cont)
					return ;
				i++;
				break ;
			}
			current = current->next;
			out->data[i].cont = ft_strdup((char *)current->content);
			if (!out->data[i].cont)
			{
				free(tmp);
				return ;
			}
		}
		else if (out->data[i].type == STR || out->data[i].type == EXPAND_STR)
		{
			if (ft_strlen(tmp) < 2)
				out->data[i].cont = ft_strdup("");
			else
				out->data[i].cont = ft_substr(tmp, 1, ft_strlen(tmp) - 2);
			if (!out->data[i].cont)
			{
				free(tmp);
				out->data[i].cont = ft_strdup("");
				if (!out->data[i].cont)
					return ;
			}
		}
		else
		{
			out->data[i].cont = ft_strdup(tmp);
			if (!out->data[i].cont)
			{
				free(tmp);
				return ;
			}
		}
		free(tmp);
		current = current->next;
		i++;
	}
	out->size = i;
}
*/
