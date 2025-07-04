/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_insert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:54:38 by abronner          #+#    #+#             */
/*   Updated: 2025/06/26 11:50:53 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static int	env_insert_node(const char *varstr, int state, t_env *env);

static int	env_rep(const char *varstr, int state, t_env *env);

int	env_ins_soft(const char *varstr, int state, t_env *env)
{
	if (!env_contains(varstr, env))
		return (1);
	return (env_ins(varstr, state, env));
}

int	env_ins(const char *varstr, int state, t_env *env)
{
	if (!varstr || !env)
		return (1);
	if (!env_rep(varstr, state, env))
		return (0);
	if (env_insert_node(varstr, state, env))
		return (1);
	return (0);
}

static int	env_insert_node(const char *varstr, int state, t_env *env)
{
	t_list		*node;
	t_envnode	*envnode;

	envnode = envnode_init(varstr, state);
	if (!envnode)
		return (1);
	node = ft_lstnew((void *)envnode);
	if (!node)
		return (envnode_free(envnode), 1);
	ft_wrapadd_back(env->wrap, node);
	if (state && envnode->val)
		env_arr_ins(envnode->var, envnode->val, env);
	return (0);
}

static int	env_rep(const char *varstr, int state, t_env *env)
{
	t_envnode	*envnode;
	char		*val;
	size_t		varlen;

	envnode = env_contains(varstr, env);
	if (!envnode)
		return (1);
	varlen = 0;
	while (varstr[varlen] && varstr[varlen] != '=')
		++varlen;
	val = NULL;
	if (varstr[varlen])
	{
		++varlen;
		val = ft_strdup(varstr + varlen);
		free(envnode->val);
		envnode->val = val;
	}
	if ((state || envnode->state) && envnode->val)
	{
		envnode->state = ENVEXP;
		env_arr_rep(envnode->var, envnode->val, env);
	}
	return (0);
}
