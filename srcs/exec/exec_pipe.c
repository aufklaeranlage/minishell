/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:52:00 by abronner          #+#    #+#             */
/*   Updated: 2025/05/20 15:53:55 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

//	exec_pipe() executes one or more tokens in a s_token struct in a pipe.

int	exec_pipe(t_group *group, char **env)
{
	int		ret;
	size_t	count;
	size_t	id;
	int		*pid_arr;

	ret = 0;
	count = exec_pipe_getsize(group);
	id = pipe_chain(count, &pid_arr);
	if (id < count)
	{
		free(pid_arr);
		while (les than id)
			group = group->next;
//		if (group->type[id] >= 5 && group->type[id] <= 11)
//			ret = exec_inbuilt(group->cont[i], env, group->type[i]);
		/*else*/ if (group->type[id] == EXEC)
			ret = exec_cmd(group->cont[id], env);
		else if (group->type[id] == SHELL)
			ret = exec_shell(group->cont[id], env);
//		else if (group->type[id] == PIPE)
//			;	//	ERROR
		exit(ret);
	}
	else
		waitpid(pid_arr[group->size - 1], &ret, 0);
	free(pid_arr);
	return (childreturn(ret));
}

static size_t	exec_pipe_getsize(t_group *g)
{
	size_t	i;

	i = 0;
	while (g->exec_type == PIPE)
	{
		++i;
		g = g->next;
	}
	return (i);
}
