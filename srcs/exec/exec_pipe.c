/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:52:00 by abronner          #+#    #+#             */
/*   Updated: 2025/05/13 11:48:16 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

//	exec_pipe() executes one or more tokens in a s_token struct in a pipe.

int	exec_pipe(t_token *tok, char **env)
{
	int		ret;
	size_t	id;
	int		*pid_arr;

	ret = 0;
	id = pipe_chain(tok->size, &pid_arr);
	if (id < tok->size)
	{
		free(pid_arr);
		if (tok->type[i] >= 5 && tok->type[i] <= 11)
			ret = exec_inbuilt(tok->cont[i], env, tok->type[i]);
		else if (tok->type[id] == EXEC)
			ret = exec_cmd(tok->cont[id], env);
		else if (tok->type[id] == SHELL)
			ret = exec_shell(tok->cont[id], env);
//		else if (tok->type[id] == PIPE)
//			;	//	ERROR
		exit(ret);
	}
	else
		waitpid(pid_arr[tok->size - 1], &ret, NULL);
	free(pid_arr);
	return (childreturn(ret));
}
