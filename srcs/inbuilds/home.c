/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 09:58:16 by abronner          #+#    #+#             */
/*   Updated: 2025/06/24 17:01:09 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inbuilds.h"

static char	*tilde_replace(char *str, t_env *env);

//	expands the tilde in the first spot of strign str. If HOME isn't set or
//	malloc fails it prints an error and returns 1. on success returns 0 and
//	replaces the str pointed to by str.

int	tilde_exp(char **str, t_env *env)
{
	char	*ret;

	if (!*str || (*str)[0] != '~')
		return (0);
	ret = tilde_replace((*str), env);
	if (!ret)
		return (1);
	free(*str);
	*str = ret;
	return (0);
}

static char	*tilde_replace(char *str, t_env *env)
{
	char	*tilde;
	char	*ret;
	int		pos;

	pos = 2;
	if (str[1] == '+')
		tilde = env_getval("PWD", env);
	else if (str[1] == '-')
		tilde = env_getval("OLDPWD", env);
	else
	{
		tilde = env_getval("HOME", env);
		--pos;
	}
	if (str[pos + 1] != '/' && str[pos + 1] != '\0')
		return (NULL);
	if (!tilde)
		return (errormsg(SHNAME, "tilde", "HOME not set", NULL), NULL);
	ret = ft_strjoin(tilde, str + pos);
	if (!ret)
		return (errormsg(SHNAME, "tilde", strerror(errno), NULL), NULL);
	return (ret);
}

//	Used for prompt shortening
//	replaces the string pointed to by str with a tidle shortened version of it.

int	tilde_ret(char **str, t_env *env)
{
	char	*tilde;
	char	*ret;
	size_t	len;

	tilde = env_getval("HOME", env);
	if (!*str || !tilde)
		return (1);
	len = ft_strlen(tilde);
	if (ft_strncmp(tilde, *str, len))
		return (0);
	if ((*str)[len] != '/' && (*str)[len] != '\0')
		return (0);
	--len;
	(*str)[len] = '~';
	ret = ft_strdup((*str) + len);
	if (!ret)
		return (errormsg(SHNAME, "tilde", strerror(errno), NULL), 1);
	free(*str);
	*str = ret;
	return (0);
}

char	*construct_prompt(t_env *env)
{
	char	*dir;
	char	*usr;
	char	*ret;
	size_t	sizes[2];
	size_t	pos;

	dir = getcurdir();
	usr = env_getval("USER", env);
	if (!usr)
		usr = RL_PROMPT;
	if (!dir || !env)
		return (free(dir), NULL);
	tilde_ret(&dir, env);
	sizes[0] = ft_strlen(usr);
	sizes[1] = ft_strlen(dir);
	ret = malloc(sizes[0] + sizes[1] + 4);
	if (!ret)
		return (free(dir), NULL);
	pos = ft_strlcpy(ret, usr, sizes[0] + 1);
	ret[pos++] = ':';
	pos += ft_strlcpy(ret + pos, dir, sizes[1] + 1);
	ft_strlcpy(ret + pos, "$ ", 3);
	return (free(dir), ret);
}
