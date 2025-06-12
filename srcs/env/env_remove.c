/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_remove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:49:00 by abronner          #+#    #+#             */
/*   Updated: 2025/06/12 10:38:33 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static void	env_rmv_node(t_env *env, t_envnode *envnode);

static void	env_rmv_connectlist(t_list *node);

//	env_removes() removes a variable of the name varstr from the environment
//	env. If the variable is removed, not present, or the environment is empty
//	1 is returned. On a failure to allocate memory space for the new environment
//	0 is returned.

int	env_rmv(const char *varstr, t_env *env)
{
	t_envnode	*envnode;

	if (!varstr || !env)
		return (0);
	envnode = env_contains(varstr, env);
	if (!envnode || ft_strncmp(envnode->var, varstr, ft_strlen(varstr)))
		return (1);
	env_rmv_node(env, envnode);
	env_arr_rmv(varstr, env);
	return (0);
}

static void	env_rmv_node(t_env *env, t_envnode *envnode)
{
	t_list	*node;

	node = env->wrap->head;
	if (node->content == (void *)envnode)
		return (ft_wrapdelfirst(env->wrap, &envnode_free_wrapper));
	while (node->next && node->next->content != (void *)envnode)
		node = node->next;
	if (!node->next->next)
		return (ft_wrapdellast(env->wrap, &envnode_free_wrapper));
	env_rmv_connectlist(node);
	env->wrap->size--;
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
