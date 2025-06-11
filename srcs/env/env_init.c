/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:16:05 by abronner          #+#    #+#             */
/*   Updated: 2025/06/11 10:41:15 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static t_env	*env_allocate(char **env);

static int		env_saveparts(t_env *ret, char **env);

t_env	*env_init(char **env)
{
	t_env	*ret;

	if (!env)
		return (NULL);
	ret = env_allocate(env);
	if (!ret)
		return (NULL);
	ret->constructed = NULL;
	if (env_saveparts(ret, env))
		return (env_free(ret), NULL);
	ret->constructed = env_construct(ret);
	if (!ret->constructed)
		return (env_free(ret), NULL);
	return (ret);
}

static t_env	*env_allocate(char **env)
{
	t_env	*ret;
	
	ret = malloc(sizeof(*ret));
	if (!ret)
		return (NULL);
	ret->size = ft_splitcount((const char **)env);
	ret->var = malloc((ret->size + 1) * sizeof(ret->var));
	ret->val = malloc((ret->size + 1) * sizeof(ret->val));
	ret->state = malloc((ret->size + 1) * sizeof(ret->state));
	if (!ret->var || !ret->val || !ret->state)
		return (free(ret->var), free(ret->val),	free(ret->state), NULL);
	return (ret);
}

static int	env_saveparts(t_env *ret, char **env)
{
	char	*var;
	char	*val;
	size_t	i;

	i = 0;
	while (i < ret->size)
	{
		if (env_splitvarstr(env[i], &var, &val))
			return (env_free(ret), 1);
		ret->var[i] = var;
		ret->val[i] = val;
		ret->state[i] = ENVEXP;
		++i;
	}
	ret->var[i] = NULL;
	ret->val[i] = NULL;
	return (0);
}
