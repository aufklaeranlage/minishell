/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:25:28 by abronner          #+#    #+#             */
/*   Updated: 2025/06/24 09:43:41 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minichill.h"
#include "exec.h"

static int	exec_shell_grploop(t_group *grp, int cond, t_env *env, int ret);

static int	exec_shell_child(t_group *grp, t_env *env);

int	exec_first(t_group *grp, t_env *env)
{
	int		ret;
	int		cond;
	t_group	*cur;

	// exec_reddir(grp->red);
	cur = grp;
	ret = 0;
	if (cur->exec_type == PIPE)
		ret = exec_shell_child(cur, env);
	else if (cur->data_type >= INCMD_ECHO
		&& cur->data_type <= INCMD_UNSET)
		ret = exec_inbuilt(cur, env);
	else
		ret = exec_shell_child(cur, env);
	while (cur->exec_type == PIPE)
		cur = cur->next;
	cond = cur->exec_type;
	cur = cur->next;
	ret = exec_shell_grploop(cur, cond, env, ret);
	return (ret);
}

//	Returns value of last executable.

int	exec_shell(t_group *grp, t_env *env)
{
	int		ret;
	int		cond;
	t_group	*cur;

	exec_reddir(grp->red);
	grp->red = NULL;
	cur = grp;
	ret = 0;
	if (cur->exec_type == PIPE)
		ret = exec_shell_child(cur, env);
	else if (cur->data_type >= INCMD_ECHO
		&& cur->data_type <= INCMD_UNSET)
		ret = exec_inbuilt(cur, env);
	else
		ret = exec_shell_child(cur, env);
	while (cur->exec_type == PIPE)
		cur = cur->next;
	cond = cur->exec_type;
	cur = cur->next;
	ret = exec_shell_grploop(cur, cond, env, ret);
	return (childreturn(ret));
}

static int	exec_shell_grploop(t_group *grp, int cond, t_env *env, int ret)
{
	while (grp)
	{
		if (cond == SMCLN || (cond == AND && !ret)
			|| (cond == OR && ret))
		{
			// cond = grp->exec_type;
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
		cond = grp->exec_type;
		if (grp->next == NULL)
			break ;
		grp = grp->next;
	}
	return (ret);
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
