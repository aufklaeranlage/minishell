/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:30:52 by abronner          #+#    #+#             */
/*   Updated: 2025/06/30 13:17:35 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static char	**tilde_pwd(const char *str, const char *val, size_t depth, t_env *env);

static char	**tilde_userhome(const char *str, size_t depth, t_env *env);

static char	**tilde_home(const char *str, size_t depth, t_env *env);

//	Check for the proper tilde value:
//		
//		A '+' after a tilde means $PWD
//		A '-' after a tilde means $OLDPWD
//
//	Only expands if a '/', space, or NUL is given after the '+' or '-'
//
//		If no '+' or '-' is specified, $HOME is taken as a value.
//
//	Expands if a '/', space, or NUL is given.
//	If any alpahabetic character is given after it checks the '/home' directory
//	for a folder of that name and if present unfolds that folder.

char	**tilde_expander(const char *str, size_t depth, t_env *env)
{
	char **ret;

	if (str[1] == '+')
		return (tilde_pwd(str + 2, env_getval("PWD", env), depth, env));
	else if (str[1] == '-')
		return (tilde_pwd(str + 2, env_getval("OLDPWD", env), depth, env));
	else if (ft_isalpha(str[1]))
		return (tilde_home(str + 2, depth, env));
	else if (ft_isspace(str[1]) || str[1] == '/' || !str[1])	
		return (tilde_userhome(str + 1, depth, env));
	ret = expander_main(str, 1, depth, env);
	if (ret && ret[depth])
		ret[depth][0] = '~';
	return (ret);
}

static char	**tilde_pwd(const char *str, const char *val, size_t depth, t_env *env)
{
	char	**ret;
	size_t	vallen;

	if (!val)
		return (NULL);
	vallen = ft_strlen(val);
	ret = expander_main(str, vallen, depth, env);
	if (ret && ret[depth])
		ft_strncpy(ret[depth], (char *)val, vallen);
	return (ret);
}

static char	**tilde_userhome(const char *str, size_t depth, t_env *env)
{
	char	**ret;
	char	*val;
	size_t	vallen;

	val = env_getval("HOME", env);
	if (!val)
		return (NULL);
	vallen = ft_strlen(val);
	ret = expander_main(str, vallen, depth, env);
	if (ret && ret[depth])
		ft_strncpy(ret[depth], val, vallen);
	return (ret);
}

static char	**tilde_home(const char *str, size_t depth, t_env *env)
{
	char	**ret;
	char	*val;
	size_t	vallen;
	char	*user;
	size_t	userlen;

	val = env_getval("HOME", env);
	if (!val)
		return (NULL);
	user = ft_strrchr(val, '/');
	if (!user)
		return (NULL);
	vallen = user - val - 1;
	user = ft_strdup("/");
	userlen = ft_strlen(user);
	ret = expander_main(str, vallen + userlen, depth, env);
	if (!ret || !ret[depth])
		return (ret);
	ft_strncpy(ret[depth], val, vallen);
	ft_strncpy(ret[depth] + vallen, user, userlen);
	return (ret);
}
