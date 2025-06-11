/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_construct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:33:27 by abronner          #+#    #+#             */
/*   Updated: 2025/06/11 11:51:14 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static char	*env_constructvarstr(char *var, char *val);

int	env_replaceconstructed(t_env *env)
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
		if (env->state[i] == ENVEXP && env->val[i])
		{
			ret[j] = env_constructvarstr(env->var[i], env->val[i]);
			if (!ret[j])
				return (ft_freesplit(ret), NULL);
			++j;
		}
		++i;
	}
	ret[j] = NULL;
	return (ret);
}

static char	*env_constructvarstr(char *var, char *val)
{
	char	*ret;
	char	*tmp;

	if (!var)
		return (NULL);
	if (!val)
		return (ft_strdup(var));
	tmp = ft_strjoin(var, "=");
	if (!tmp)
		return (NULL);
	ret = ft_strjoin(tmp, val);
	free(tmp);
	return (ret);
}
