/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_inbuilt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:31:56 by abronner          #+#    #+#             */
/*   Updated: 2025/06/26 16:28:41 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "inbuilds.h"

static int	ret_inbuilts(t_group *grp, t_env *env);

int	exec_inbuilt(t_group *grp, t_env *env)
{
	int			fd[2];
	int			ret;

	fd[0] = dup(STDIN);
	fd[1] = dup(STDOUT);
	if (handle_quotes((t_tokens *)grp->data, env)
		|| handle_quotes(grp->red, env))
		return (1);
	if (exec_reddir(grp->red))
		return (2);
	if (tmp_assign((t_tokens *)grp->data, env))
		return (3);
	ret = ret_inbuilts(grp, env);
	env_rmv_tmp(env);
	dup2(fd[0], STDIN);
	dup2(fd[1], STDOUT);
	return (ret);
}

static int	ret_inbuilts(t_group *grp, t_env *env)
{
	t_tokens	*tok;

	tok = (t_tokens *)grp->data;
	if (!tok || !tok->type)
		return (-1);
	if (tok->type[0] == INCMD_ECHO)
		return (ft_echo(tok, env));
	else if (tok->type[0] == INCMD_PWD)
		return (ft_pwd(tok));
	else if (tok->type[0] == INCMD_CD)
		return (ft_cd(tok, env));
	else if (tok->type[0] == INCMD_ENV)
		return (ft_env(env));
	else if (tok->type[0] == INCMD_EXPORT)
		return (ft_export(tok, env));
	else if (tok->type[0] == INCMD_UNSET)
		return (ft_unset(tok, env));
	else if (tok->type[0] == INCMD_EXIT)
		ft_exit();
	return (-1);
}
