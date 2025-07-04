/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:55:19 by abronner          #+#    #+#             */
/*   Updated: 2025/06/30 14:17:15 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "errors.h"

static char	**singlequotes_expander(const char *s, size_t total, int depth, t_env *env);

static char	**doublequotes_expander(const char *s, size_t total, int depth, t_env *env);

static char	**quotesparam_expander(const char *s, size_t total, int depth, t_env *env);

int	split_expander(char *src, char ***dst, t_env *env)
{
	size_t	dcount;
	char	**ret;
	size_t	i;

	if (!dst)
		return (1);
	dcount = 0;
	if (!*dst)
		dcount = ft_splitcount((const char **)(*dst));
	// ret = tilde_expander(src, env, dcount);
	i = 0;
	while (ft_isspace(src[i]))
		++i;
	ret = expander_main(src + i, 0, dcount, env);
	if (!ret)
		return (1);
	while (dcount--)
		ret[dcount] = (*dst)[dcount];
	free(*dst);
	*dst = ret;
	return (1);
}

char	**expander_main(const char *s, size_t total, size_t depth, t_env *env)
{
	char	**ret;
	size_t	i;
	size_t	len;

	i = 0;
	while (ft_isspace(s[i]))
		++i;
	len = expander_skippre(s + i);
	if (total == 0 && s[i] == '~')
		return (tilde_expander(s, depth, env));
	if (!s[i + len] && !total && !len)
		ret = ft_calloc(depth + 1, sizeof(*ret));
	else if (!s[i + len] || ft_isspace(s[0]))
	{
		ret = expander_main(s + i + len, 0, depth + 1, env);
		ret[depth] = malloc((total + len + 1) * sizeof(*ret[depth]));
		ret[depth][total] = '\0';
	}
	if (s[i + len] == '"')
		ret = doublequotes_expander(s + i + len, total + len, depth, env);
	else if (s[i + len] == '\'')
		ret = singlequotes_expander(s + i + len, total + len, depth, env);
	else if (s[i + len] == '$')
		ret = param_expander(s + i + len, total + len, depth, env);
	if (ret && ret[depth])
		ft_strncpy(ret[depth] + total, (char *)(s + i), len);
	return (ret);
}

static char	**singlequotes_expander(const char *s, size_t total, int depth, t_env *env)
{
	char	**ret;
	size_t	i;

	i = 1;
	while (s[i] && s[i] != '\'')
		++i;
	if (!s[i])
		return (errormsg(SHNAME, "expander", "missing \'", NULL), NULL);
	ret = expander_main(s + i, total + i - 2, depth, env);
	if (ret && ret[depth])
		ft_strncpy(ret[depth] + total, (char *)s, i);
	return (ret);
}

static char	**doublequotes_expander(const char *s, size_t total, int depth, t_env *env)
{
	char	**ret;
	size_t	first;
	size_t	i;

	i = 0;
	first = (s[i] == '"');
	while (s[i + first] && s[i + first] != '"' && s[i + first] != '$')
		++i;
	if (s[i + first] == '$')
		ret = quotesparam_expander(s + i + first, total + i, depth, env);
	else if (s[i + first] == '"')
		ret = expander_main(s + i + first + 1, total + i, depth, env);
	else if (ret && ret[depth])
		ft_strncpy(ret[depth] + total, (char *)(s + first), i - 1);
	else
		return (errormsg(SHNAME, "expander", "missing \"", NULL), NULL);
	return (ret);
}

static char	**quotesparam_expander(const char *s, size_t total, int depth, t_env *env)
{
	char	**ret;
	char	*val;
	size_t	vallen;
	size_t	varlen;

	val = env_getval(s + 1, env);
	varlen = 1;
	while (s[varlen] && !ft_strchr(VAR_DEL, s[varlen]))
		++varlen;
	vallen = varlen;
	if (val)
		vallen = ft_strlen(val);
	else
		val = (char *)s;
	if (s[varlen] != '"')
		ret = doublequotes_expander(s + varlen, total + vallen, depth, env);
	else
		ret = expander_main(s + varlen + 1, total + vallen, depth, env);
	if (ret && ret[depth])
		ft_strncpy(ret[depth] + total, val, vallen);
	return (ret);
}

size_t	expander_skippre(const char *str)
{
	size_t	i;
	
	i = 0;
	while (str[i] && str[i] != '$' && str[i] != '\'' && str[i] != '"')
		++i;
	return (i);
}
