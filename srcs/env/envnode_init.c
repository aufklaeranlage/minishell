/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envnode_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 12:08:32 by abronner          #+#    #+#             */
/*   Updated: 2025/06/24 09:22:23 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

//	envnode_init() initializes a envnode with val, var and state set, depending
//	on the input. The varstr is split into two strigns that get malloced and
//	saved. The given varstr needs to be freed by the caller.

t_envnode	*envnode_init(const char *varstr, int state)
{
	t_envnode	*ret;
	char		*var;
	char		*val;

	ret = malloc(sizeof(*ret));
	if (!varstr || !ret)
		return (free(ret), NULL);
	if (env_splitvarstr(varstr, &var, &val))
		return (envnode_free(ret), NULL);
	ret->var = var;
	ret->val = val;
	ret->state = state;
	return (ret);
}

//	envnode_init_sep() initializes an envnode with val, var and state set.
//	It creates copys of var and val. If the given variables were malloced by
//	the caller they need to be freed by the caller.

t_envnode	*envnode_init_sep(const char *var, const char *val, int state)
{
	t_envnode	*ret;
	char		*var_cpy;
	char		*val_cpy;

	ret = malloc(sizeof(*ret));
	if (!var || !val || !ret)
		return (free(ret), NULL);
	var_cpy = ft_strdup(var);
	val_cpy = ft_strdup(val);
	if (!var_cpy || !val_cpy)
		return (free(ret), free(var_cpy), free(val_cpy), NULL);
	ret->var = var_cpy;
	ret->val = val_cpy;
	ret->state = state;
	return (ret);
}

void	envnode_free(t_envnode *envnode)
{
	free(envnode->var);
	free(envnode->val);
	free(envnode);
}

void	envnode_free_wrapper(void *envnode)
{
	envnode_free((t_envnode *)envnode);
}
