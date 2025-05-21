/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:44:45 by abronner          #+#    #+#             */
/*   Updated: 2025/05/21 12:47:36 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char *cmd_getbin(char *name, char **env);

//	exec_cmd:
//		Executes a single command (array of string) stored in a token.
//		If there are assignments before the string of arrays it will change
//		it's environment, which will have no effects on the other processes

int	exec_cmd(t_group *group, char **env)
{
	int		pid;
	char	*bin;
	size_t	i;

	if (exec_reddir(group->red))
		;	//	FREE EVERYTHING MALLOC ERROR
	i = exec_assign((t_token *)group->data, &env);
	if (group->data_type != STD_CMD)
		;	//	ERROR	: tokenizer err
	bin = cmd_getbin(((t_token *)group->data)->content[i], env);
	if (!bin)
		return (errormsg((char *)group->cont[i], "command not found"), -1);
	if (execve(bin, (char **)(group->cont + i), env) == -1)
		;	//	ERROR	: execve fail
	//	FREE EVERYTHING (Maybe needs to be done up the tree)
	return (127);
}

//	cmd_getbin() gets the proper pinary

static char *cmd_getbin(char *name, char **env)
{
	char	**paths;
	char	*bin;
	char	*tmp;
	size_t	i;

	i = 0;
	paths = ft_split(ft_getenv("PATH", env), ':' );
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (ft_freesplit(paths), NULL);
		bin = ft_strjoin(tmp, execname);
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
