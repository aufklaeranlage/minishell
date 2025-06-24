/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inbuilds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:58:58 by akuzmin           #+#    #+#             */
/*   Updated: 2025/06/24 16:05:32 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inbuilds.h"
#include "exec.h"

static int	ret_inbuilts(t_group *grp, t_env *env);

int	inbuilds(t_group *grp, t_env *env)
{
	int			fd[2];
	int			ret;

	fd[0] = 0;
	fd[1] = 0;
	dup2(STDIN, fd[0]);
	dup2(STDOUT, fd[1]);
	if (exec_reddir(grp->red))
		return (-1);
	ret = ret_inbuilts(grp, env);
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
		return (ft_pwd());
	else if (tok->type[0] == INCMD_CD)
		return (ft_cd(tok, env));
	else if (tok->type[0] == INCMD_ENV)
		return (ft_env(env));
	else if (tok->type[0] == INCMD_EXPORT)
		return (ft_export(tok, env));
	else if (tok->type[0] == INCMD_UNSET)
		return (ft_unset(tok, env));
	else if (tok->type[0] == INCMD_EXIT)
		return (ft_exit(grp));
	return (-1);
}
