/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:30:49 by abronner          #+#    #+#             */
/*   Updated: 2025/05/21 11:28:39 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <stdlib.h>

# include "pipe.h"
# include "errors.h"
# include "env.h"
# include "tokenisation.h"

//	SHELL

int		exec_shell(t_tokens *tok, char **env);

//	CMD

int		exec_cmd(t_tokens *tok, char **env);

//	RED DIR

int		exec_reddir(t_tokens *tok);

//	RED DIR HEREDOC

int		open_heredoc(char *hd_str);

//	UTILS

size_t	exec_assign(t_tokens *tok, char ***env);

int		childreturn(int wstatus);

#endif
