/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:44:08 by abronner          #+#    #+#             */
/*   Updated: 2025/06/17 12:51:51 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	env_varrepval(const char *var, const char *val, t_env *env)
{
	char		*newval;
	t_envnode	*envnode;

	envnode = env_contains(var, env);
	if (!envnode)
		return (errormsg(SHNAME, "env", var, "not contained"), 1);
	newval = ft_strdup(val);
	if (!newval)
		return (errormsg(SHNAME, "env", "malloc error", NULL), 1);
	if (env_arr_rep(var, val, env))
		return (1)
	free(envnode->val);
	envnode->val = newval;
	return (0);
}
