/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:52:03 by abronner          #+#    #+#             */
/*   Updated: 2025/06/10 14:51:34 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

//	env_contains() checks if a variable with the name of varname exists in the
//	environment env. If it does it returns it's position, otherwise it
//	returns 0.
//	env_contains() starts counting positions at 1, so there is no overlap
//	between the flase reutnr value (0) and the first position (0 in an array).

size_t	env_contains(char *var, t_env *env)
{
	size_t	varlen;
	size_t	i;

	varlen = 0;
	while (var[varlen] && var[varlen] != '=' )
		++varlen;
	++varlen;
	i = 1;
	while (i <= env->size)
	{
		if (!ft_strncmp(var, env->var[i - 1], varlen))
			return (i);
		++i;
	}
	return (0);
}

int	env_splitvarstr(char *vatstr, char **var, char **val)
{
	tmp = ft_strchr(varstr, '=');
	if (tmp)
	{
		*var = ft_substr(varstr, 0, tmp - varstr);
		*val = ft_substr(varstr, tmp - varstr, ft_strlen(varstr));
		if (!val)
			return (free(*var), 1);
	}
	else
	{
		*var = ft_strdup(varstr);
		*val = NULL;
	}
	if (!*var)
		return (free(*val), 1);
	return (0);
}

char	*env_constructvarstr(char *var, char *val)
{
	char	*ret;
	char	*tmp;

	tmp = ft_strjoin(var, "=");
	if (!tmp)
		return (NULL);
	ret = ft_strjoin(tmp, val);
	free(tmp);
	return (ret);
}

size_t	env_expsize(t_env *env)
{
	size_t	ret;
	size_t	i;

	ret = 0;
	i = 0;
	while (i < env->size)
	{
		if (env->state[i] == ENVEXP && env->val)
			++ret;
		++i;
	}
	return (ret);
}

void	env_free(t_env *env)
{
	ft_splitfree(var);
	ft_splitfree(val);
	ft_splitfree(constructed);
	free(state);
}
