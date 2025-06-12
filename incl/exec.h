/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:30:49 by abronner          #+#    #+#             */
/*   Updated: 2025/06/12 10:48:24 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <stdlib.h>

# include "shell.h"
# include "inbuilds.h"
# include "libft.h"
# include "pipe.h"
# include "errors.h"
# include "env.h"
# include "tokenisation.h"

//	WRAPPER

int		exec_wrapper(t_group *grp, t_env *env);

//	SHELL

int		exec_shell(t_group *grp, t_env *env);

//	PIPE

int		exec_pipe(t_group *grp, t_env *env);

//	CMD

int		exec_cmd(t_group *grp, t_env *env);

//	INBUILT CMD

int		exec_inbuilt(t_group *grp, t_env *env);

//	RED DIR

int		exec_reddir(t_tokens *tok);

//	RED DIR HEREDOC

int		open_heredoc(char *hd_str);

//	UTILS

int		exec_assign(t_tokens *tok, t_env *env);

int		childreturn(int wstatus);

//	CLEANUP

void	exec_cleanup(t_shell *shell);

void	group_free(t_group *grp);

#endif
