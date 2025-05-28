/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_wrapper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:12:28 by abronner          #+#    #+#             */
/*   Updated: 2025/05/27 15:43:29 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_wrapper(t_group *group, char ***env)
{
	int	ret;
	int	pid;

	if (!group)
		return (1);
	ret = 0;
	if (group->exec_type == PIPE)
		ret = exec_pipe(group, *env);
	else if (group->data_type == STD_CMD)
	{
		pid = fork();
		if (!pid)
			exec_cmd(group, *env);
		waitpid(pid, &ret, 0);
		ret = childreturn(ret);
	}
	else if (group->data_type >= INCMD_ECHO && group->data_type <= INCMD_UNSET)
		ret = exec_inbuilt(group, env);
	else if (group->data_type == GROUP)
		ret = exec_shell(group->data, env);
	return (ret);
}
