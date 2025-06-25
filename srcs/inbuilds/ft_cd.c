/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:58:58 by akuzmin           #+#    #+#             */
/*   Updated: 2025/06/25 12:52:49 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inbuilds.h"
#include "env.h"
#include "errors.h"

static int	cd_minus(char *str,t_env *env);

static int	cd_home(t_env *env);

static int	cd_absolut(char *str, t_env *env);

static int	cd_updateenv(char *oldpwd, t_env *env);

//	cd needs to:
//		change directory
//		detect minus ('-') flag
//		update the environments PWD and OLDPWD variables
//		
//	cd utilities need to:
//		expand dots ('.' && '..')

int	ft_cd(t_tokens *tok, t_env *env)
{
	char	*oldpwd;

	if (tok->size > 2)
		return (errormsg(SHNAME, "cd", "only takes 1 argument", NULL), 1);
	oldpwd = getcurdir();
	if (!oldpwd)
		return (errormsg(SHNAME, "cd", strerror(errno), NULL), 1);
	if (tok->size == 1)
		cd_home(env);
	else if (tok->content[1][0] == '-')
		cd_minus(tok->content[1], env);
	else
		cd_absolut(tok->content[1], env);
	cd_updateenv(oldpwd, env);
	free(oldpwd);
	return (0);
}

static int	cd_home(t_env *env)
{
	char	*dir;

	dir = env_getval("HOME", env);
	if (!dir)
		return (errormsg(SHNAME, "cd", "HOME not set", NULL), 1);
	if (chdir(dir) == -1)
		return (errormsg(SHNAME, "cd", dir, strerror(errno)), 1);
	return (0);
}

static int	cd_minus(char *str,t_env *env)
{
	char	*dir;

	if (str[1] != '\0')
		return (errormsg(SHNAME, "cd", str, "invalid option")
		, 2);
	dir = env_getval("OLDPWD", env);
	if (!dir)
		return (errormsg(SHNAME, "cd", "OLDPWD not set", NULL), 2);
	if (chdir(dir) == -1)
		return (errormsg(SHNAME, "cd", dir, strerror(errno)), 2);
	return (1);
}

static int	cd_absolut(char *str, t_env *env)
{
	int		ret;
	char	*dir;

	ret = 0;
	dir = ft_strdup(str);
	if (tilde_exp(&dir, env))
		ret = 1;
	if (chdir(dir) == -1)
		ret = 1;
	if (ret)
		errormsg(SHNAME, "cd", str, strerror(errno));
	free(dir);
	return (ret);
}

//	Updates the environment: sets the value of PWD to OLDPWD and stores the
//	directory the shell moved to as PWD

static int	cd_updateenv(char *oldpwd, t_env *env)
{
	char	*pwd;

	pwd = getcurdir();
	if ((!pwd || env_ins_sep("PWD", pwd, ENVSET, env))
		&& env_ins_sep("OLDPWD", oldpwd, ENVSET, env))
		return (free(pwd), 1);
	return (0);
}

//	Initializes PWD and OLDPWD in the environment. It calls getcurdir to get the
//	current directory.

void	init_pwd(t_env *env)
{
	char	*dir;

	dir = getcurdir();
	if (dir)
		env_ins_sep("PWD", dir, ENVEXP, env);
	free(dir);
}
