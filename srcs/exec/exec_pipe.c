/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:52:00 by abronner          #+#    #+#             */
/*   Updated: 2025/06/12 10:49:39 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static size_t	exec_pipe_getsize(t_group *grp);

static void		exec_pipe_child(t_group *grp, size_t id, t_env *env);

static int		exec_pipe_wait(int count, int *pid_arr);

//	exec_pipe() executes one or more tokens in a s_token struct in a pipe.

int	exec_pipe(t_group *grp, t_env *env)
{
	int		ret;
	size_t	count;
	size_t	id;
	int		*pid_arr;

	ret = 0;
	count = exec_pipe_getsize(grp);
	id = pipe_chain(count, &pid_arr);
	if (id < count)
	{
		free(pid_arr);
		exec_pipe_child(grp, id, env);
	}
	else
		ret = exec_pipe_wait(count, pid_arr);
	free(pid_arr);
	return (childreturn(ret));
}

static size_t	exec_pipe_getsize(t_group *grp)
{
	size_t	i;

	i = 1;
	while (grp->exec_type == PIPE)
	{
		++i;
		grp = grp->next;
	}
	return (i);
}

static void	exec_pipe_child(t_group *grp, size_t id, t_env *env)
{
	size_t	ret;

	while (id)
	{
		grp = grp->next;
		--id;
	}
	ret = 0;
	if (grp->data_type >= INCMD_ECHO && grp->data_type <= INCMD_UNSET)
	{
		ret = exec_inbuilt(grp, env);
		exec_cleanup(grp->shell);
	}
	else if (grp->data_type == STD_CMD)
		ret = exec_cmd(grp, env);
	else if (grp->data_type == GROUP)
		ret = exec_shell(grp, env);
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
