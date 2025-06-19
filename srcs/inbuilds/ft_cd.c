/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:58:58 by akuzmin           #+#    #+#             */
/*   Updated: 2025/06/17 13:07:56 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inbuilds.h"
#include "env.h"
#include "errors.h"

static void	cd_updatepwd(const char *dir, t_env *env);

int	init_pwd(t_env *env)
{
	char	*dir;
	char	*dir_cpy;
	size_t	size;

	size = 64;
	dir = malloc(size * sizeof(*dir));
	while (!getcwd(dir, size))
	{
		if (errno != ERANGE)
			return (errormsg(SHNAME, "getcwd", strerror(errno)))
		size *= 2;
		free(dir);
		dir = malloc(size* sizeof(*dir));
	}
	dir_cpy = ft_strdup(dir);
	env_varrepval("PWD", dir, env);
	env_varrepval("OLDPWD", dir_cpy, env);
}

int ft_cd(t_tokens *tokens, t_env *env)
{
	char *dir;

	if (tok->size > 2)
		return (errormsg(SHNAME, "cd", "too many arguments", NULL), 1);
	if (tok->content[1][0] == '-')
	{
		if (tok->content[1][1] != '\0')
			return (errormsg(SHNAME,"cd",tok->content[1],"invalid option"), 2);
		dir = env_getval("OLDPWD", env);	
	}
	else
		dir = tokens->content[1];
	if (chdir(dir) == -1)
		return (errormsg(SHNAME, "cd", tok->content[1], strerror(errno)), 1);
	cd_updatepwd(dir, env);
	return (0);
}

static void	cd_updatepwd(const char *dir, t_env *env)
{
	char	*oldpwd;

	oldpwd = env_getval("PWD");
	env_varrepval("PWD", dir, env);
	if (oldpwd)
		env_varrepval("OLDPWD", oldpwd, env);
}
