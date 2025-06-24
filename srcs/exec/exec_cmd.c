/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:44:45 by abronner          #+#    #+#             */
/*   Updated: 2025/06/24 14:50:15 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*cmd_getbin(char *name, t_env *env);

//	exec_cmd:
//		Executes a single command (array of string) stored in a token.
//		If there are assignments before the string of arrays it will change
//		it's environment, which will have no effects on the other processes

int	exec_cmd(t_group *grp, t_env *env)
{
	char	**argv;
	char	*bin;

	if (exec_reddir(grp->red))
		return (1);
	exec_assign((t_tokens *)grp->data, env);
	argv = ((t_tokens *)grp->data)->content;
	bin = cmd_getbin(argv[0], env);
	if (!bin)
		return (errormsg(SHNAME, argv[0], "command not found", NULL), 127);
	execve(bin, argv, env->arr);
	return (errormsg(SHNAME, argv[0], strerror(errno), NULL), 126);
}

//	cmd_getbin() gets the proper pinary

static char	*cmd_getbin(char *name, t_env *env)
{
	char	**paths;
	char	*bin;
	char	*tmp;
	size_t	i;

	i = 0;
	if (ft_strrchr(name, '/') && access(name, F_OK | X_OK) == 0)
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
