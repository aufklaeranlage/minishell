/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:23:46 by abronner          #+#    #+#             */
/*   Updated: 2025/05/28 15:28:04 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

//	All the groups should point to the t_shell struct, from which we can free
//	everything.

typedef struct s_shell
{
	char	**exp;		// EXPORT
	char	**env;		// ENVIRONMENT
	t_group	*cmd;
	//	READLINE??
}	t_shell;

#endif
