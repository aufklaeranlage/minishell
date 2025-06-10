/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_remove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:49:00 by abronner          #+#    #+#             */
/*   Updated: 2025/06/10 14:50:13 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static t_envstate	*env_statermv(t_envstate *state, size_t	pos, size_t	size);

static int			env_remove_parts(size_t pos, t_env *env);

//	env_removes() removes a variable of the name varname from the environment
//	env. If the variable is removed, not present, or the environment is empty
//	1 is returned. On a failure to allocate memory space for the new environment
//	0 is returned.

int	env_remove(char *varname, t_env *env)
{
	size_t	pos;

	if (!varname || !env)
		return (0);
	pos = env_contains(varname, *env);
	if (!pos--)
		return (0);
	if (env_removeparts(env, pos))
		return (1);
	env_replaceconstructed(env);
	return (0);
}

static int	env_removeparts(t_env *env, size_t pos)
{
	char 	**tmpvar;
	char 	**tmpval;
	char 	**tmpstate;

	tmpvar = ft_splitrmv(env->var, pos);
	tmpval = ft_splitrmv(env->val, pos);
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

static t_envstate	*env_statermv(int *state, size_t	pos, size_t	size)
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
