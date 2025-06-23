/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_arr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:33:27 by abronner          #+#    #+#             */
/*   Updated: 2025/06/23 08:58:53 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	env_arr_init(t_env *env)
{
	t_list		*node;
	t_envnode	*envnode;
	size_t		j;

	env->arr = malloc((env_expsize(env) + 1) * sizeof(env->arr));
	if (!env->arr)
		return (1);
	node = env->wrap->head;
	j = 0;
	while (node)
	{
		envnode = (t_envnode *)(node->content);
		if (envnode->state == ENVEXP && envnode->val)
		{
			env->arr[j] = env_constructvarstr(envnode->var, envnode->val);
			if (!env->arr[j])
				return (ft_freesplit(env->arr), 1);
			++j;
		}
		node = node->next;
	}
	env->arr[j] = NULL;
	return (0);
}

int	env_arr_ins(const char *var, const char *val, t_env *env)
{
	char	*cpy;
	char	**tmp;
	size_t	size;
	size_t	i;

	cpy = env_constructvarstr(var, val);
	size = env_expsize(env);
	tmp = malloc((size + 1) * sizeof(*tmp));
	if (!tmp || !cpy)
		return (free(tmp), free(cpy), 1);
	i = 0;
	while (i + 1 < size)
	{
		tmp[i] = env->arr[i];
		++i;
	}
	tmp[i++] = cpy;
	tmp[i] = NULL;
	free(env->arr);
	env->arr = tmp;
	return (0);
}

int	env_arr_rep(const char *var, const char *val, t_env *env)
{
	char	*cpy;
	size_t	varlen;
	size_t	i;

	cpy = env_constructvarstr(var, val);
	if (!cpy)
		return (1);
	varlen = ft_strlen(var);
	i = 0;
	while (env->arr[i])
	{
		if (!ft_strncmp(var, env->arr[i], varlen) && env->arr[i][varlen] == '=')
		{
			free(env->arr[i]);
			env->arr[i] = cpy;
			break ;
		}
		++i;
	}
	if (!env->arr[i])
		return (free(cpy), env_arr_ins(var, val, env));
	return (0);
}

int	env_arr_rmv(const char *varstr, t_env *env)
{
	char	**src;
	char	**tmp;
	size_t	varlen;
	size_t	size;
	size_t	i;

	size = env_expsize(env);
	tmp = malloc((size + 1) * sizeof(*tmp));
	if (!tmp)
		return (1);
	varlen = ft_strlen(varstr);
	i = 0;
	src = env->arr;
	while (*src)
	{
		if (!ft_strncmp(varstr, *src, varlen) && (*src)[varlen] == '=')
			free(*src);
		else
			tmp[i++] = *src;
		++src;
	}
	tmp[i] = NULL;
	free(env->arr);
	env->arr = tmp;
	return (0);
}
