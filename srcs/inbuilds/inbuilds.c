/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inbuilds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:58:58 by akuzmin           #+#    #+#             */
/*   Updated: 2025/07/04 13:44:35 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inbuilds.h"
#include "exec.h"

static int	ret_inbuilts(t_group *grp, t_env *env);

int	inbuilds(t_group *grp, t_env *env)
{
	int			fd[2];
	int			ret;

	if (handle_quotes((t_tokens *)grp->data, env))
		return (1);
	fd[0] = dup(STDIN);
	fd[1] = dup(STDOUT);
	if (exec_reddir(grp->red, env))
		return (1);
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
		return (ft_exit(tok, grp));
	return (-1);
}
