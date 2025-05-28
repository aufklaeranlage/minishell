/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:25:28 by abronner          #+#    #+#             */
/*   Updated: 2025/05/28 15:21:27 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minichill.h"
#include "exec.h"

static int	exec_shell_child(t_group *group, char **env);

//	Returns value of last executable.

int	exec_shell(t_group *group, char ***env)
{
	int		ret;
	int		cond;

	exec_reddir(group->red);
	ret = 0;
	cond = group->exec_type;
	if (group->exec_type == PIPE)
		ret = exec_shell_child(group, *env);
	else if (group->data_type >= INCMD_ECHO
		&& group->data_type <= INCMD_UNSET)
		ret = exec_inbuilt(group, env);
	else
		ret = exec_shell_child(group, *env);
	while (group->exec_type == PIPE)
		group = group->next;
	group = group->next;
	while (group)
	{
		if (cond == SMCLN || (cond == AND && !ret)
			|| (cond == OR && ret))
		{
			cond = group->exec_type;
			if (group->exec_type == PIPE)
				ret = exec_shell_child(group, *env);
			else if (group->data_type >= INCMD_ECHO
				&& group->data_type <= INCMD_UNSET)
				ret = exec_inbuilt(group, env);
			else
				ret = exec_shell_child(group, *env);
			while (group->exec_type == PIPE)
				group = group->next;
		}
		if (group->next == NULL)
			break ;
		group = group->next;
	}
	return (childreturn(ret));
}

static int	exec_shell_child(t_group *group, char **env)
{
	int		ret;
	pid_t	pid;

	ret = 0;
	pid = fork();
	if (!pid)
	{
		if (group->exec_type == PIPE)
			ret = exec_pipe(group, env);
		else if (group->data_type == STD_CMD)
			ret = exec_cmd(group, env);
		else if (group->data_type == GROUP)
			ret = exec_shell(group->data, &env);
		exit(ret);
	}
	else
		waitpid(pid, &ret, 0);
	return (childreturn(ret));
}
