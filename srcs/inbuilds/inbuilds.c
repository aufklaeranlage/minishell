/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inbuilds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:58:58 by akuzmin           #+#    #+#             */
/*   Updated: 2025/06/23 15:04:50 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inbuilds.h"

int	inbuilds(t_group *grp, t_env *env)
{
	t_tokens	*tok;

	tok = (t_tokens *)grp->data;
	if (!tok->type)
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
