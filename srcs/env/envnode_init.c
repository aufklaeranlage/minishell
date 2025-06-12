/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envnode_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 12:08:32 by abronner          #+#    #+#             */
/*   Updated: 2025/06/12 10:20:29 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

//	envnode_init() initializes a envnode with val, var and state set, depending
//	on the input. The given varstr isn't freed.

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
