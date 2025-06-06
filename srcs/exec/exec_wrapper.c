/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_wrapper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:12:28 by abronner          #+#    #+#             */
/*   Updated: 2025/06/06 15:24:58 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_wrapper(t_group *grp, char ***env)
{
	int	ret;
	int	pid;

	if (!grp)
		return (1);
	ret = 0;
	if (grp->exec_type == PIPE)
		ret = exec_pipe(grp, *env);
	else if (grp->data_type == STD_CMD)
	{
		pid = fork();
		if (!pid)
			exec_cmd(grp, *env);
		waitpid(pid, &ret, 0);
		ret = childreturn(ret);
	}
	else if (grp->data_type >= INCMD_ECHO && grp->data_type <= INCMD_UNSET)
		ret = exec_inbuilt(grp, env);
	else if (grp->data_type == GROUP)
		ret = exec_shell(grp->data, env);
	group_free(grp);
	return (ret);
}
