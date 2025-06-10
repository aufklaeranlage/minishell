/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_construct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:33:27 by abronner          #+#    #+#             */
/*   Updated: 2025/06/10 14:49:05 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int		env_replaceconstructed(t_env *env)
{
	char	**tmp;

	tmp = env_construct(env);
	if (!tmp)
		return (1);
	ft_freesplit(env->constructed);
	env->constructed = tmp;
	return (0);
}

char	**env_construct(t_env *env)
{
	char	**ret;
	size_t	size;
	size_t	i;
	size_t	j;

	size = env_expsize(env) + 1;
	ret = malloc((size--) * sizeof(ret));
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	while (i < env->size)
	{
		if (env->state[i] == ENVEXP && env->val)
		{
			ret[j] = env_constructvarstr(env->var[i], env->val[i]);
			if (!ret[j])
				return (ft_splitfree(ret), NULL);
			++j;
		}
		++i;
	}
	ret[j] = NULL;
	return (ret);
}
