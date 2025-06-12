/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:44:45 by abronner          #+#    #+#             */
/*   Updated: 2025/06/12 10:48:50 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char *cmd_getbin(char *name, t_env *env);

//	exec_cmd:
//		Executes a single command (array of string) stored in a token.
//		If there are assignments before the string of arrays it will change
//		it's environment, which will have no effects on the other processes

int	exec_cmd(t_group *grp, t_env *env)
{
	char	**argv;
	char	*bin;

	if (exec_reddir(grp->red))
		exec_cleanup(grp->shell);
	exec_assign((t_tokens *)grp->data, env);
	argv = ((t_tokens *)grp->data)->content;
	bin = cmd_getbin(argv[0], env);
	if (!bin)
		return (errormsg(SHNAME, argv[0], "command not found", NULL), -1);
	if (execve(bin, argv, env->arr) == -1)
		exec_cleanup(grp->shell);
	return (127);
}

//	cmd_getbin() gets the proper pinary

static char *cmd_getbin(char *name, t_env *env)
{
	char	**paths;
	char	*bin;
	char	*tmp;
	size_t	i;

	i = 0;
	paths = ft_split(env_getval(name, env), ':' );
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (ft_freesplit(paths), NULL);
		bin = ft_strjoin(tmp, name);
		free(tmp);
		if (!bin)
			return (ft_freesplit(paths), NULL);
		if (access(bin, F_OK | X_OK) == 0)
			return (ft_freesplit(paths), bin);
		free(bin);
		++i;
	}
	return (ft_freesplit(paths), NULL);
}
