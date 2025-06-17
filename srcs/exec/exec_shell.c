/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:25:28 by abronner          #+#    #+#             */
/*   Updated: 2025/06/17 12:20:04 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minichill.h"
#include "exec.h"

static int	exec_shell_child(t_group *grp, t_env *env);

//	Returns value of last executable.

int	exec_shell(t_group *grp, t_env *env)
{
	int		ret;
	int		cond;

	exec_reddir(grp->red);
	ret = 0;
	cond = grp->exec_type;
	if (grp->exec_type == PIPE)
		ret = exec_shell_child(grp, env);
	else if (grp->data_type >= INCMD_ECHO
		&& grp->data_type <= INCMD_UNSET)
		ret = exec_inbuilt(grp, env);
	else
		ret = exec_shell_child(grp, env);
	while (grp->exec_type == PIPE)
		grp = grp->next;
	grp = grp->next;
	while (grp)
	{
		if (cond == SMCLN || (cond == AND && !ret)
			|| (cond == OR && ret))
		{
			cond = grp->exec_type;
			if (grp->exec_type == PIPE)
				ret = exec_shell_child(grp, env);
			else if (grp->data_type >= INCMD_ECHO
				&& grp->data_type <= INCMD_UNSET)
				ret = exec_inbuilt(grp, env);
			else
				ret = exec_shell_child(grp, env);
			while (grp->exec_type == PIPE)
				grp = grp->next;
		}
		if (grp->next == NULL)
			break ;
		grp = grp->next;
	}
	return (exec_cleanup(grp->shell), childreturn(ret));
}

static int	exec_shell_child(t_group *grp, t_env *env)
{
	int		ret;
	pid_t	pid;

	ret = 0;
	pid = fork();
	if (!pid)
	{
		if (grp->exec_type == PIPE)
			ret = exec_pipe(grp, env);
		else if (grp->data_type == STD_CMD)
			ret = exec_cmd(grp, env);
		else if (grp->data_type == SHELL)
			ret = exec_shell(grp->data, env);
		exec_cleanup(grp->shell);
		exit(ret);
	}
	else
		waitpid(pid, &ret, 0);
	return (childreturn(ret));
}
