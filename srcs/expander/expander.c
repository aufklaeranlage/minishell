/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:05:41 by abronner          #+#    #+#             */
/*   Updated: 2025/06/12 09:32:06 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static char	*expander_getvar(char *var, t_env *env);

static char	*expander_initret(char *str, size_t offset, size_t len);

char	*expander(char *str, t_env *env, size_t offset)
{
	char	*ret;
	char	*rep;
	size_t	i;
	size_t	var_len;
	size_t	rlen;

	i = 0;
	while (str[i] && str[i] != '$')
		++i;
	if (!str[i])
		return (expander_initret(str, offset, i));
	var_len = 1;
	while (str[i + var_len] && !ft_strchr(VAR_DEL, str[i + var_len]))
		++var_len;
	rep = expander_getvar(str + i + 1, env);
	rlen = 0;
	if (rep)
		rlen = ft_strlen(rep);
	ret = expander(str + i + var_len, env, offset + i + rlen);
	if (!ret)
		return (NULL);
	ft_strncpy(ret + offset, str, i);
	if (rep)
		ft_strncpy(ret + offset + i, rep, rlen);
	return (ret);
}

static char	*expander_getvar(char *var, t_env *env)
{
	t_envnode	*envnode;

	if (!var || !env)
		return (NULL);
	envnode = env_contains(var, env);
	if (!envnode)
		return (NULL);
	return (envnode->val);
}

static char	*expander_initret(char *str, size_t offset, size_t len)
{
	char	*ret;

	ret = malloc((offset + len + 1) * sizeof(*ret));
	if (!ret)
		return (NULL);
	ret[offset + len] = '\0';
	ft_strncpy(ret + offset, str, len);
	return (ret);
}
