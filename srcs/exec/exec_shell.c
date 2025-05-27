/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:25:28 by abronner          #+#    #+#             */
/*   Updated: 2025/05/26 12:44:56 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minichill.h"
#include "exec.h"

static int	exec_shell_child(t_group *group, int type, char **env);

static int	exec_inbuilt(t_group *group, char ***env);

//	Returns value of last executable.

int	exec_shell(t_group *group, char ***env)
{
	int		ret;

	exec_reddir(group->red);
	ret = 0;
	while (group)
	{
		if (group->exec_type == SMCLN || (group->exec_type == AND && !ret)
			|| (group->exec_type == OR && ret))
		{
			if (group->data_type >= INCMD_ECHO
				&& group->data_type <= INCMD_UNSET)
				ret = exec_inbuilt(group, env);
			else
				ret = exec_shell_child(group, group->data_type, *env);
			while (group->exec_type == PIPE)
				group = group->next;
		}
		if (group->next == NULL)
			break ;
		group = group->next;
	}
	return (childreturn(ret));
}

static int	exec_shell_child(t_group *group, int type, char **env)
{
	int		ret;
	pid_t	pid;

	ret = 0;
	pid = fork();
	if (!pid)
	{
		if (type == STD_CMD)
			ret = exec_cmd(group, env);
		else if (type == GROUP)
			ret = exec_shell(group, &env);
		else if (group->exec_type == PIPE)
			ret = exec_pipe(group, env);
		exit(ret);
	}
	else
		waitpid(pid, &ret, 0);
	return (childreturn(ret));
}

static int	exec_inbuilt(t_group *group, char ***env)
{
	t_tokens *token;

	token = (t_tokens *)group->data;
	inbuilds(token, *env);
	return (0);
}
