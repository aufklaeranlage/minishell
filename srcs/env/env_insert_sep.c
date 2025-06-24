/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_insert_sep.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:54:38 by abronner          #+#    #+#             */
/*   Updated: 2025/06/24 09:33:24 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static int	env_ins_sep_node(const char *var, const char *val, int exp,
				t_env *env);

static int	env_rep_sep(const char *var, const char *val, int exp, t_env *env);

int	env_ins_sep(const char *var, const char *val, int exp, t_env *env)
{
	if (!var || !val || !env)
		return (1);
	if (!env_rep_sep(var, val, exp, env))
		return (0);
	if (env_ins_sep_node(var, val, exp, env))
		return (1);
	return (0);
}

static int	env_ins_sep_node(const char *var, const char *val, int exp,
			t_env *env)
{
	t_list		*node;
	t_envnode	*envnode;

	envnode = envnode_init_sep(var, val, exp);
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

static int	env_rep_sep(const char *var, const char *val, int exp, t_env *env)
{
	t_envnode	*envnode;
	char		*val_cpy;

	envnode = env_contains(var, env);
	if (!envnode)
		return (1);
	val_cpy = ft_strdup(val);
	free(envnode->val);
	envnode->val = val_cpy;
	if ((exp || envnode->state) && envnode->val)
	{
		envnode->state = ENVEXP;
		env_arr_rep(envnode->var, envnode->val, env);
	}
	return (0);
}
