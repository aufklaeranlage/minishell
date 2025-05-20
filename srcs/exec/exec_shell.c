/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:25:28 by abronner          #+#    #+#             */
/*   Updated: 2025/05/19 15:06:34 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	exec_shell_child(void *cont, int type, char **env);

//	Returns value of last executable.

int	exec_shell(t_token *tok, char **env)
{
	int		ret;
	int		pid;
	size_t	i;

	exec_reddir(tok);
	ret = 0;
	i = 0;
	while (i < tok->size)
	{
		//	EXECUTE IF LOGIC IS CORRECT
		if ((tok->logic[i] == AND && !ret) || (tok->logic[i] == OR && ret))
		{
			//	DON'T EXECUTE INBUILTS IN CHILDREN
			if (tok->type[i] >= 5 && tok->type[i] <= 11)
				ret = exec_inbuilt(tok->cont[i], env, tok->type[i]);
			else
				ret = exec_shell_child(tok->cont[i], tok->type[i], env);
		}
		++i;
	}
	return (childreturn(ret));
}

static int	exec_shell_child(void *cont, int type, char **env)
{
	int		ret;
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		if (type == EXEC)
			ret = exec_cmd(cont, env);
		else if (type == SHELL)
			ret = exec_shell(cont, env);
		else if (type[i] == PIPE)
			ret = exec_pipe(cont, env);
		exit(ret);
	}
	else
		waitpid(pid, &ret, NULL);
	return (ret);
}
