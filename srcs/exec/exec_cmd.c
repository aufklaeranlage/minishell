/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:44:45 by abronner          #+#    #+#             */
/*   Updated: 2025/07/05 18:06:04 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

static char	*cmd_getbin(char *name, char *env_path);

static int	permission_check(char *name, char *bin)
{
	DIR		*dir;

	dir = opendir(name);
	if (dir && bin)
		return (closedir(dir), 126);
	closedir(dir);
	if (!bin)
	{
		if (ft_strrchr(name, '/'))
			return (127);
		else
			return (127);
	}
	return (0);
}

static int	permission_error(char *name, char *bin, int type)
{
	if (type == 126)
		return (errormsg(SHNAME, name, "Is a directory", NULL), 126);
	if (!bin && type == 127)
	{
		if (ft_strrchr(name, '/'))
			return (errormsg(SHNAME, name, "No such file or directory", NULL), \
			127);
		else
			return (errormsg(SHNAME, name, "command not found", NULL), 127);
	}
	return (0);
}

//	exec_cmd:
//		Executes a single command (array of string) stored in a token.
//		If there are assignments before the string of arrays it will change
//		it's environment, which will have no effects on the other processes

int	exec_cmd(t_group *grp, t_env *env)
{
	char	**argv;
	char	*bin;

	if (exec_reddir(grp->red, env))
		return (1);
	argv = ((t_tokens *)grp->data)->content;
	if (!((t_tokens *)grp->data)->size)
		return (0);
	bin = cmd_getbin(argv[0], env_getval("PATH", env));
	if (permission_check(argv[0], bin))
		return (permission_error(argv[0], bin, permission_check(argv[0], bin)));
	execve(bin, argv, env->arr);
	if (access(bin, F_OK) != 0)
		return (errormsg(SHNAME, argv[0], "No such file or directory", NULL), \
		127);
	else
		return (errormsg(SHNAME, argv[0], "Permission denied", NULL), 126);
}

//	cmd_getbin() gets the proper pinary
//
//	Bash checks:
//		File exists				(access F_OK)
//		File is not a directory	(opendir)
//		File is executable		(access X_OK)
//
//	Check PATH first. If nothing in path matches we take the original name
//	'name' given to the function as 'bin'.
//	'bin' gets checked for 1. existence, 2. not being a directory, and
//	3. being executable. 

static char	*cmd_getbin(char *name, char *env_path)
{
	char	**paths;
	char	*bin;
	char	*tmp;
	size_t	i;

	i = 0;
	if (!env_path || (ft_strrchr(name, '/') && access(name, F_OK) == 0))
		return (name);
	paths = ft_split(env_path, ':' );
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (ft_freesplit(paths), NULL);
		bin = ft_strjoin(tmp, name);
		free(tmp);
		if (!bin || access(bin, F_OK | X_OK) == 0)
			return (ft_freesplit(paths), bin);
		free(bin);
		++i;
	}
	return (ft_freesplit(paths), NULL);
}
