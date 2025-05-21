/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:54:38 by abronner          #+#    #+#             */
/*   Updated: 2025/05/21 17:33:58 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static int		env_replace(char *var, char **env);

static size_t	env_contains(char *varname, char **env);

static void		env_cpy(size_t count, size_t pos, char **new, char **env);

//	env_insert() inserts a given variable assignment that consists of a
//	variable name and a variable name seperated by an equal sign at the end
//	of the previous existing env split supplied through the pointer env.

int	env_insert(char *var, char ***env)
{
	char	**new;
	size_t	count;
	size_t	i;
	
	if (!env_replace(var, *env))
		return (0);
	count = ft_splitcount((const char **)(*env));
	new = malloc((count + 2) * sizeof(*new));
	if (!new)
		return (1);
	i = 0;
	while (i < count)
	{
		new[i] = (*env)[i];
		++i;
	}
	new[i] = var;
	new[i + 1] = NULL;
	free(*env);
	*env = new;
	return (0);
}

static int	env_replace(char *var, char **env)
{
	size_t	pos;

	if (!env)
		return (1);
	pos = env_contains(var, env);
	if (!pos--)
		return (1);	//	VAR NOT IN ENV
	free(env[pos]);
	env[pos] = var;
	return (0);
}

//	env_removes() removes a variable of the name varname from the environment
//	env. If the variable is removed, not present, or the environment is empty
//	1 is returned. On a failure to allocate memory space for the new environment
//	0 is returned.

int	env_remove(char *varname, char ***env)
{
	char 	**new;
	size_t	pos;

	if (!varname || !env || !*env || !**env)
		return (0);
	pos = env_contains(varname, *env);
	if (!pos--)
		return (0);
	new = ft_splitrmv(*env, pos);
	if (!new)
		return (1);
	free((*env)[pos]);
	free(*env);
	*env = new;
	return (0);
}

//	env_contains() checks if a variable with the name of varname exists in the
//	environment env. If it does it returns it's position, otherwise it
//	returns 0.

static size_t	env_contains(char *var, char **env)
{
	size_t	varlen;
	size_t	i;

	varlen = 0;
	while (var[varlen] && var[varlen] != '=' )
		++varlen;
	++varlen;
	i = 1;
	while (i > 0 && env[i - 1])
	{
		if (!ft_strncmp(var, env[i - 1], varlen))
			return (i);
		++i;
	}
	return (0);
}
