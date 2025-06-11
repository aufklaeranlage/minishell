/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_remove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:49:00 by abronner          #+#    #+#             */
/*   Updated: 2025/06/11 15:51:15 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static void	env_rmv_connectlist(t_list *node);

//	env_removes() removes a variable of the name varname from the environment
//	env. If the variable is removed, not present, or the environment is empty
//	1 is returned. On a failure to allocate memory space for the new environment
//	0 is returned.

int	env_rmv(char *varname, t_env *env)
{
	t_envnode	*envnode;
	t_list		*node;

	if (!varname || !env)
		return (0);
	envnode = env_contains(varname, env);
	if (!envnode)
		return (1);
	node = env->wrap->head;
	if (node->content == (void *)envnode)
		ft_wrapdelfirst(env->wrap, &envnode_free_wrapper);
	else
	{
		while (node->next && node->next->content != (void *)envnode)
			node = node->next;
		if (!node->next->next)
			ft_wrapdellast(env->wrap, &envnode_free_wrapper);
		else
		{
			env_rmv_connectlist(node);
			env->wrap->size--;
		}
	}
	env_arr_rmv(varname, env);
	return (0);
}

static void	env_rmv_connectlist(t_list *node)
{
	t_list	*nnnode;

	if (!node || !node->next)
		return ;
	nnnode = node->next->next;
	ft_lstdelone(node->next, &envnode_free_wrapper);
	node->next = nnnode;
}
