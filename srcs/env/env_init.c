/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:16:05 by abronner          #+#    #+#             */
/*   Updated: 2025/06/11 12:59:39 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static t_env	*env_init_alloc(void);

static int		env_init_add(t_env *ret, char **env);

t_env	*env_init(char **envsplit)
{
	t_env	*ret;

	if (!envsplit)
		return (NULL);
	ret = env_init_alloc();
	if (!ret)
		return (ret);
	if (env_init_add(ret, envsplit))
		return (NULL);
	if (env_arr_init(ret))
		return (env_free(ret), NULL);
	return (ret);
}

static t_env	*env_init_alloc(void)
{
	t_env	*ret;

	ret = malloc(sizeof(*ret));
	if (!ret)
		return (NULL);
	ret->wrap = malloc(sizeof(*(ret->wrap)));
	if (!ret->wrap)
		return (free(ret), NULL);
	ret->wrap->head = NULL;
	ret->wrap->tail = NULL;
	ret->arr = NULL;
	return (ret);
}

static int	env_init_add(t_env *ret, char **env)
{
	size_t		i;
	t_envnode	*cont;
	t_list		*node;

	if (!ret || !env)
		return (1);
	i = 0;
	while (env[i])
	{
		cont = envnode_init(env[i], ENVEXP);
		if (!cont)
			return (env_free(ret), 1);
		node = ft_lstnew((void *)cont);
		if (!node)
			return (envnode_free(cont), env_free(ret), 1);
		ft_wrapadd_back(ret->wrap, node);
		++i;
	}
	return (0);
}

void	env_free(t_env *env)
{
	if (!env)
		return ;
	if (env->wrap)
		ft_wrapclear(env->wrap, &envnode_free_wrapper);
	if (env->arr)
		ft_freesplit(env->arr);
	free(env);
}
