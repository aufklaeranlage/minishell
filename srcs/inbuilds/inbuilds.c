/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inbuilds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:58:58 by akuzmin           #+#    #+#             */
/*   Updated: 2025/05/26 14:39:38 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inbuilds.h"

int	inbuilds(t_tokens *tokens, char **env)
{
	if (!tokens->type)
		return (-1);
	if (tokens->type[0] == INCMD_ECHO)
		return (ft_echo(tokens, env));
	else if (tokens->type[0] == INCMD_PWD)
		return (ft_pwd());
	else if (tokens->type[0] == INCMD_CD)
		return (ft_cd(tokens, env));
	else if (tokens->type[0] == INCMD_ENV)
		return (ft_env(env));
	else if (tokens->type[0] == INCMD_EXPORT)
		return (ft_export(env));
	else if (tokens->type[0] == INCMD_UNSET)
		return (ft_unset(tokens, &env));
	else if (tokens->type[0] == INCMD_EXIT)
		return (ft_exit(tokens, env));
	return (-1);
}
