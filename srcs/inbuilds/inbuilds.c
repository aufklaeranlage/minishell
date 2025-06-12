/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inbuilds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:58:58 by akuzmin           #+#    #+#             */
/*   Updated: 2025/06/12 11:08:07 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inbuilds.h"

int	inbuilds(t_tokens *tok, t_env *env)
{
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
		return (ft_exit(tok, env));
	return (-1);
}
