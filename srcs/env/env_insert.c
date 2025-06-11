/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_insert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:54:38 by abronner          #+#    #+#             */
/*   Updated: 2025/06/11 11:01:08 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static int	env_insert_parts(char *nvar, char *nval, int exp, t_env *env);

static int	env_replace(char *var, char *val, int exp, t_env *env);

static int	env_parts_init(size_t size, char ***var, char ***val, int **state);

static void	env_parts_copy(char **var, char **val, int *state, t_env *env);

int	env_insert(char *varstr, int exp, t_env *env)
{
	char	*var;
	char	*val;

	if (!varstr || !env)
		return (1);
	if (env_splitvarstr(varstr, &var, &val))
		return (1);
	if (!env_replace(var, val, exp, env))
		return (0);
	if (env_insert_parts(var, val, exp, env))
		return (free(var), free(val), 1);
	env_replaceconstructed(env);
	return (0);
}

static int	env_insert_parts(char *nvar, char *nval, int exp, t_env *env)
{
	char	**var;
	char	**val;
	int		*state;

	if (env_parts_init(env->size + 1, &var, &val, &state))
		return (1);
	env_parts_copy(var, val, state, env);
	var[env->size] = nvar;
	val[env->size] = nval;
	state[env->size] = (exp != 0) * ENVEXP | (exp == 0) * ENVSET;
	free(env->var);
	free(env->val);
	free(env->state);
	env->var = var;
	env->val = val;
	env->state = state;
	++env->size;
	return (0);
}

static int	env_replace(char *var, char *val, int exp, t_env *env)
{
	size_t	pos;

	pos = env_contains(var, env);
	if (!pos--)
		return (1);
	free(env->var[pos]);
	env->var[pos] = var;
	free(env->val[pos]);
	env->val[pos] = val;
	if (exp)
		env->state[pos] = ENVEXP;
	env_replaceconstructed(env);
	return (0);
}

static int	env_parts_init(size_t size, char ***var, char ***val, int **state)
{
	++size;
	*var = malloc(size * (sizeof(**var)));
	*val = malloc(size * (sizeof(**val)));
	*state = malloc(size * (sizeof(**state)));
	if (!*var || !*val || !*state)
		return (ft_freesplit(*var), ft_freesplit(*val), free(*state),
			errormsg(SHNAME, "env", ENVERRINS, NULL), 1);
	(*var)[size - 1] = NULL;
	(*val)[size - 1] = NULL;
	(*state)[size - 1] = 0;
	return (0);
}

static void	env_parts_copy(char **var, char **val, int *state, t_env *env)
{
	size_t	i;

	i = 0;
	while (i < env->size)
	{
		var[i] = env->var[i];
		val[i] = env->val[i];
		state[i] = env->state[i];
		++i;
	}
}
