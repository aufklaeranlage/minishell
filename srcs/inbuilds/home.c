/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 09:58:16 by abronner          #+#    #+#             */
/*   Updated: 2025/06/24 10:47:43 by abronner         ###   ########.fr       */
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
	if ((*str)[len--] != '/')
		return (0);
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
	char	*ret;
	size_t	sizes[2];
	size_t	pos;

	dir = getcurdir();
	if (!dir || !env)
		return (free(dir), NULL);
	sizes[0] = ft_strlen(RL_PROMPT);
	sizes[1] = ft_strlen(dir);
	ret = malloc(sizes[0] + sizes[1] + 4);
	if (!ret)
		return (free(dir), NULL);
	pos = ft_strlcpy(ret, RL_PROMPT, sizes[0] + 1);
	ret[pos++] = ':';
	pos += ft_strlcpy(ret + pos, dir, sizes[1] + 1);
	ft_strlcpy(ret + pos, "$ ", 3);
	return (free(dir), ret);
}
