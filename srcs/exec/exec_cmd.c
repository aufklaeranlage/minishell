/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:44:45 by abronner          #+#    #+#             */
/*   Updated: 2025/07/04 18:20:25 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	exec_error(char *name, char *bin);

//	exec_cmd:
//		Executes a single command (array of string) stored in a token.
//		If there are assignments before the string of arrays it will change
//		it's environment, which will have no effects on the other processes

int	exec_cmd(t_group *grp, t_env *env)
{
	char	**argv;
	char	*bin;

	if (handle_quotes((t_tokens *)grp->data, env))
		return (1);
	// argv = ((t_tokens *)grp->data)->content;
	if (exec_reddir(grp->red, env))
		return (1);
	if (tmp_assign((t_tokens *)grp->data, env))
		return (1);
	// exec_assign((t_tokens *)grp->data, env);
	argv = ((t_tokens *)grp->data)->content;
	if (!((t_tokens *)grp->data)->size)
		return (0);
	bin = cmd_getbin(argv[0], env);
	if (!bin)
		return (errormsg(SHNAME, argv[0], "command not found", NULL), 127);
	execve(bin, argv, env->arr);
	return (exec_error(argv[0], bin));
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

static char	*cmd_getbin(char *name, t_env *env)
{
	char	**paths;
	char	*bin;
	char	*tmp;
	size_t	i;

	i = 0;
	if (ft_strrchr(name, '/') && access(name, F_OK) == 0)
		return (name);
	paths = ft_split(ft_getenv("PATH", env->arr), ':' );
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
