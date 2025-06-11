/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_remove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:49:00 by abronner          #+#    #+#             */
/*   Updated: 2025/06/11 11:01:39 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static int	*env_statermv(int *state, size_t pos, size_t size);

static int	env_removeparts(t_env *env, size_t pos);

static char	**env_splitrmv(char **split, size_t pos, size_t size);

//	env_removes() removes a variable of the name varname from the environment
//	env. If the variable is removed, not present, or the environment is empty
//	1 is returned. On a failure to allocate memory space for the new environment
//	0 is returned.

int	env_remove(char *varname, t_env *env)
{
	size_t	pos;

	if (!varname || !env)
		return (0);
	pos = env_contains(varname, env);
	if (!pos--)
		return (0);
	if (env_removeparts(env, pos))
		return (1);
	env_replaceconstructed(env);
	return (0);
}

static int	env_removeparts(t_env *env, size_t pos)
{
	char	**tmpvar;
	char	**tmpval;
	int		*tmpstate;

	tmpvar = env_splitrmv(env->var, pos, env->size);
	tmpval = env_splitrmv(env->val, pos, env->size);
	tmpstate = env_statermv(env->state, pos, env->size);
	if (!tmpvar || !tmpval || !tmpstate)
		return (errormsg(SHNAME, "env", ENVERRSPC, NULL), free(tmpvar),
			free(tmpval), free(tmpstate), 1);
	free(env->var[pos]);
	free(env->var);
	env->var = tmpvar;
	free(env->val[pos]);
	free(env->val);
	env->val = tmpval;
	free(env->state);
	env->state = tmpstate;
	env->size--;
	return (0);
}

static int	*env_statermv(int *state, size_t pos, size_t	size)
{
	int		*ret;
	size_t	i;

	if (!state || pos > size)
		return (NULL);
	ret = malloc(size * sizeof(*ret));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < pos)
	{
		ret[i] = state[i];
		++i;
	}
	while (i < size)
	{
		ret[i] = state[i];
		++i;
	}
	return (ret);
}

static char	**env_splitrmv(char **split, size_t pos, size_t size)
{
	char	**ret;
	size_t	i;

	if (!split)
		return (NULL);
	if (pos > size)
		return (NULL);
	ret = malloc(size-- * sizeof(*ret));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < pos)
	{
		ret[i] = split[i];
		++i;
	}
	while (i < size)
	{
		ret[i] = split[i + 1];
		++i;
	}
	ret[i] = NULL;
	return (ret);
}
