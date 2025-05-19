/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:54:38 by abronner          #+#    #+#             */
/*   Updated: 2025/05/19 12:41:15 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static size_t	env_contains(char *varname, char **env);

static void		env_cpy(size_t count, size_t pos, char **tmp, char **env);

//	env_insert() inserts a given variable assignment that consists of a
//	variable name and a variable name seperated by an equal sign at the end
//	of the previous existing env split supplied through the pointer env.

int	env_insert(char *var, char ***env)
{
	char	**tmp;
	size_t	count;
	size_t	i;
	
	count = ft_splitcount((const char **)(*env));
	tmp = malloc((count + 2) * sizeof(*tmp));
	if (!tmp)
		return (1);
	i = 0;
	while (i < count)
	{
		tmp[i] = (*env)[i];
		++i;
	}
	tmp[i] = var;
	tmp[i + 1] = NULL;
	free(*env);
	*env = tmp;
	return (0);
}

//	env_removes() removes a variable of the name varname from the environment
//	env. If the variable is removed, not present, or the environment is empty
//	1 is returned. On a failure to allocate memory space for the new environment
//	0 is returned.

int	env_remove(char *varname, char ***env)
{
	char 	**tmp;
	size_t	pos;
	size_t	count;

	count = ft_splitcount((const char **)(*env));
	pos = env_contains(varname, *env);
	if (!count || !pos)
		return (1);
	tmp = malloc(count * sizeof(*tmp));
	if (!tmp)
		return (0);
	env_cpy(count, pos, tmp, *env);
	free((*env)[pos]);
	free(*env);
	tmp[count] = NULL;
	*env = tmp;
	return (1);
}

//	env_contains() checks if a variable with the name of varname exists in the
//	environment env. If it does it returns it's position, otherwise it
//	returns 0.

static size_t	env_contains(char *varname, char **env)
{
	size_t	varlen;
	size_t	i;

	varlen = ft_strlen(varname);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(varname, env[i], varlen))
			return (i);
		++i;
	}
	return (0);
}

//	env_cpy() copies everything except the string at pos from env to tmp.

static void	env_cpy(size_t count, size_t pos, char **tmp, char **env)
{
	size_t	i;

	i = 0;
	while (i < pos)
	{
		tmp[i] = env[i];
		++i;
	}
	while (i < count)
	{
		tmp[i] = env[i + 1];
		++i;
	}
}
