/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:52:00 by abronner          #+#    #+#             */
/*   Updated: 2025/06/06 09:15:18 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static size_t	exec_pipe_getsize(t_group *group);

static void		exec_pipe_child(t_group *group, size_t id, char **env);

static int		exec_pipe_wait(int count, int *pid_arr);

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
		exec_pipe_child(group, id, env);
	}
	else
		ret = exec_pipe_wait(count, pid_arr);
	free(pid_arr);
	return (childreturn(ret));
}

static size_t	exec_pipe_getsize(t_group *group)
{
	size_t	i;

	i = 1;
	while (group->exec_type == PIPE)
	{
		++i;
		group = group->next;
	}
	return (i);
}

static void	exec_pipe_child(t_group *group, size_t id, char **env)
{
	size_t	ret;

	while (id)
	{
		group = group->next;
		--id;
	}
	ret = 0;
	if (group->data_type >= INCMD_ECHO && group->data_type <= INCMD_UNSET)
	{
		ret = exec_inbuilt(group, &env);
		exec_cleanup(grp->parrent);
	}
	else if (group->data_type == STD_CMD)
		ret = exec_cmd(group, env);
	else if (group->data_type == GROUP)
		ret = exec_shell(group, &env);
	exit(ret);
}

static int	exec_pipe_wait(int count, int *pid_arr)
{
	int	ret;
	int	i;

	ret = 0;
	i = 0;
	while (i < count)
	{
		waitpid(pid_arr[i], &ret, 0);
		++i;
	}
	return (ret);
}
