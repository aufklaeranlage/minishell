/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:52:03 by abronner          #+#    #+#             */
/*   Updated: 2025/06/11 13:43:46 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_envnode	*env_contains(char *var, t_env *env)
{
	t_list		*node;
	t_envnode	*envnode;
	size_t		varlen;

	if (!var || !env)
		return (NULL);
	varlen = 0;
	while (var[varlen] && var[varlen] != '=' )
		++varlen;
	node = env->wrap->head;
	while (node)
	{
		envnode = (t_envnode *)(node->content);
		if (!ft_strncmp(var, envnode->var, varlen)
			&& envnode->var[varlen] == '\0')
			return (envnode);
		node = node->next;
	}
	return (NULL);
}

int	env_splitvarstr(char *varstr, char **var, char **val)
{
	char	*tmp;
	size_t	len;

	tmp = ft_strchr(varstr, '=');
	if (tmp)
	{
		len = tmp - varstr;
		*var = ft_substr(varstr, 0, len);
		*val = ft_substr(varstr, len + 1, ft_strlen(varstr));
		if (!val)
			return (free(*var), 1);
	}
	else
	{
		*var = ft_strdup(varstr);
		*val = NULL;
	}
	if (!*var)
		return (free(*val), 1);
	return (0);
}

size_t	env_expsize(t_env *env)
{
	size_t		ret;
	t_list		*node;
	t_envnode	*envnode;

	if (!env)
		return (0);
	ret = 0;
	node = env->wrap->head;
	while (node)
	{
		envnode = (t_envnode *)node->content;
		if (envnode->state == ENVEXP && envnode->val)
			++ret;
		node = node->next;
	}
	return (ret);
}
