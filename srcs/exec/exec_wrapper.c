/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_wrapper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:12:28 by abronner          #+#    #+#             */
/*   Updated: 2025/05/27 13:19:41 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_wrapper(t_group *group, char ***env)
{
	int	ret;
	int	pid;

	if (!group)
		return (1);
	if (group->data_type == CMD)
	{
		pid = fork();
		if (!pid)
			exec_cmd(group, *env);
		waitpid(pid, &ret, 0);
		ret = childreturn(ret);
	}
	else
		ret = exec_shell(group, env);
	return (ret);
}
