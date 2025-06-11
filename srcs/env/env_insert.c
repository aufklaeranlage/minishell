/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_insert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:54:38 by abronner          #+#    #+#             */
/*   Updated: 2025/06/11 16:15:34 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static int	env_insert_node(char *varstr, int exp, t_env *env);

static int	env_replace(char *varstr, int exp, t_env *env);

int	env_ins(char *varstr, int exp, t_env *env)
{
	if (!varstr || !env)
		return (1);
	if (!env_replace(varstr, exp, env))
		return (0);
	if (env_insert_node(varstr, exp, env))
		return (1);
	return (0);
}

static int	env_insert_node(char *varstr, int exp, t_env *env)
{
	t_list		*node;
	t_envnode	*envnode;

	envnode = envnode_init(varstr, exp);
	if (!envnode)
		return (1);
	node = ft_lstnew((void *)envnode);
	if (!node)
		return (envnode_free(envnode), 1);
	ft_wrapadd_back(env->wrap, node);
	if (exp && envnode->val)
		env_arr_ins(envnode->var, envnode->val, env);
	return (0);
}

static int	env_replace(char *varstr, int exp, t_env *env)
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
	if ((exp || envnode->state) && envnode->val)
	{
		envnode->state = ENVEXP;
		env_arr_rep(envnode->var, envnode->val, env);
	}
	return (0);
}
