/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:25:28 by abronner          #+#    #+#             */
/*   Updated: 2025/05/13 11:29:48 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "group.h"

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
			{
				//	EXECUTE ALL REGUALR COMMANDS IN CHILDREN
				pid = fork();
				if (!pid)
				{
					if (tok->type[i] == EXEC)
						ret = exec_cmd(tok->cont[i], env);
					else if (tok->type[i] == SHELL)
						ret = exec_shell(tok->cont[i], env);
					else if (tok->type[i] == PIPE)
						ret = exec_pipe(tok->cont[i], env);
					exit(ret);
				}
				else
					waitpid(pid, &ret, NULL);
			}
		}
		++i;
	}
	return (childreturn(ret));
}
