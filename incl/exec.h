/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:30:49 by abronner          #+#    #+#             */
/*   Updated: 2025/05/27 15:36:18 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <stdlib.h>

# include "inbuilds.h"
# include "libft.h"
# include "pipe.h"
# include "errors.h"
# include "env.h"
# include "tokenisation.h"

//	WRAPPER

int		exec_wrapper(t_group *group, char ***env);

//	SHELL

int		exec_shell(t_group *group, char ***env);

//	PIPE

int		exec_pipe(t_group *group, char **env);

//	CMD

int		exec_cmd(t_group *group, char **env);

//	INBUILT CMD

int		exec_inbuilt(t_group *group, char ***env);

//	RED DIR

int		exec_reddir(t_tokens *tok);

//	RED DIR HEREDOC

int		open_heredoc(char *hd_str);

//	UTILS

int		exec_assign(t_tokens *tok, char ***env);

int		childreturn(int wstatus);

#endif
