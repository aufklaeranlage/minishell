/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:23:46 by abronner          #+#    #+#             */
/*   Updated: 2025/06/24 08:43:43 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "tokenisation.h"
# include "env.h"

//	All the groups should point to the t_shell struct, from which we can free
//	everything.

typedef struct s_env	t_env;

typedef struct s_group	t_group;

typedef struct s_shell
{
	t_env	*env;		// ENVIRONMENT
	t_group	*cmd;
	char	*home;
	//	READLINE??
}	t_shell;

#endif
