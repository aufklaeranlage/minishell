/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:58:58 by akuzmin           #+#    #+#             */
/*   Updated: 2025/07/01 08:51:13 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inbuilds.h"
#include "env.h"
#include "errors.h"

/**
 * @brief Initializes PWD and OLDPWD in the environment. 
 * It calls getcurdir to get the current directory.
 * @param env 
 */
void	init_pwd(t_env *env)
{
	char	*dir;

	dir = getcurdir();
	if (dir)
		env_ins_sep("PWD", dir, ENVEXP, env);
	free(dir);
}
