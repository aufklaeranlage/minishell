/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:58:58 by akuzmin           #+#    #+#             */
/*   Updated: 2025/06/23 11:30:58 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inbuilds.h"
#include "env.h"
#include "errors.h"

static int	cd_updateenv(t_env *env);

static char	*cd_curdir();

//	cd needs to:
//		change directory
//		detect minus ('-') flag
//		update the environments PWD and OLDPWD variables
//		
//	cd utilities need to:
//		expand dots ('.' && '..')

int ft_cd(t_tokens *tok, t_env *env)
{
	char *dir;

	if (tok->size != 2)
		return (errormsg(SHNAME, "cd", "only takes 1 argument", NULL), 1);
	if (tok->content[1][0] == '-')
	{
		if (tok->content[1][1] != '\0')
			return (errormsg(SHNAME,"cd",tok->content[1],"invalid option"), 2);
		dir = env_getval("OLDPWD", env);	
	}
	else
		dir = tok->content[1];
	if (chdir(dir) == -1)
		return (errormsg(SHNAME, "cd", tok->content[1], strerror(errno)), 1);
	if (cd_updateenv(env))
		return (errormsg(SHNAME, "cd", "couldn't update environment", NULL), 1);
	return (0);
}

//	Updates the environment: sets the value of PWD to OLDPWD and stores the
//	directory the shell moved to as PWD

static int	cd_updateenv(t_env *env)
{
	char	*pwd;
	char	*oldpwd;
	char	*op_str;
	char	*p_str;

	pwd = cd_curdir();
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

//	Gets a allocated version of getcwd that can be freed and only uses it's
//	length + 1 of memoryspace. achives this by looping to enlargen a dynamically
//	allocated array of characters if a call to getcwd failed because of ERANGE.
//	At the end it calls strdup on the string and frees the probablz longer than
//	needed dznamicallz allocated buffer used with getcwd.

static char	*cd_curdir()
{
	char	*ret;
	char	*dir;
	size_t	size;

	size = 32;
	dir = malloc(size * sizeof(*dir));
	// dir = ft_calloc(size, sizeof(*dir));
	while (!getcwd(dir, size))
	{
		if (errno != ERANGE)
			return (NULL);
		size *= 2;
		free(dir);
		dir = malloc(size * sizeof(*dir));
		// dir = ft_calloc(size, sizeof(*dir));
	}
	ret = ft_strdup(dir);
	free(dir);
	return (ret);
}

//	Initializes PWD and OLDPWD in the environment. It calls getcurdir to get the
//	current directory.

int	init_pwd(t_env *env)
{
	char	*dir;
	char	*op_str;
	char	*p_str;

	dir = cd_curdir();
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
