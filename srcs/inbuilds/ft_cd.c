/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:58:58 by akuzmin           #+#    #+#             */
/*   Updated: 2025/06/24 10:30:51 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inbuilds.h"
#include "env.h"
#include "errors.h"

static int	cd_updateenv(t_env *env);

//	cd needs to:
//		change directory
//		detect minus ('-') flag
//		update the environments PWD and OLDPWD variables
//		
//	cd utilities need to:
//		expand dots ('.' && '..')

int	ft_cd(t_tokens *tok, t_env *env)
{
	char	*dir;

	if (tok->size != 2)
		return (errormsg(SHNAME, "cd", "only takes 1 argument", NULL), 1);
	if (tok->content[1][0] == '-')
	{
		if (tok->content[1][1] != '\0')
			return (errormsg(SHNAME, "cd", tok->content[1], "invalid option")
				, 2);
		dir = env_getval("OLDPWD", env);
	}
	else
		dir = tok->content[1];
	dir = ft_strdup(dir);
	if (tilde_exp(&dir, env))
		return (free(dir), 1);
	if (chdir(dir) == -1)
		return (free(dir),
			errormsg(SHNAME, "cd", tok->content[1], strerror(errno)), 1);
	if (cd_updateenv(env))
		return (free(dir),
			errormsg(SHNAME, "cd", "couldn't update environment", NULL), 1);
	return (free(dir), 0);
}

//	Updates the environment: sets the value of PWD to OLDPWD and stores the
//	directory the shell moved to as PWD

static int	cd_updateenv(t_env *env)
{
	char	*pwd;
	char	*oldpwd;
	char	*op_str;
	char	*p_str;

	pwd = getcurdir();
	oldpwd = env_getval("PWD", env);
	if (!pwd || !oldpwd)
		return (free(pwd), free(oldpwd), 1);
	p_str = env_constructvarstr("PWD", pwd);
	free(pwd);
	op_str = env_constructvarstr("OLDPWD", oldpwd);
	if (!p_str || !op_str
		|| env_ins(p_str, ENVEXP, env) || env_ins(op_str, ENVEXP, env))
		return (free(p_str), free(op_str), 1);
	free(p_str);
	free(op_str);
	return (0);
}

//	Initializes PWD and OLDPWD in the environment. It calls getcurdir to get the
//	current directory.

int	init_pwd(t_env *env)
{
	char	*dir;
	char	*op_str;
	char	*p_str;

	p_str = NULL;
	op_str = NULL;
	dir = getcurdir();
	if (dir)
	{
		p_str = env_constructvarstr("PWD", dir);
		op_str = env_constructvarstr("OLDPWD", dir);
		free(dir);
		if (!(!p_str || !op_str
				|| env_ins(p_str, ENVEXP, env) || env_ins(op_str, ENVEXP, env)))
			return (free(p_str), free(op_str), 0);
	}
	free(p_str);
	free(op_str);
	return (errormsg(SHNAME, "env", "couldn't initalize PWD", NULL), 1);
}
