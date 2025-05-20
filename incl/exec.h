/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:30:49 by abronner          #+#    #+#             */
/*   Updated: 2025/05/19 15:15:53 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <stdlib.h>

# include "pipe.h"
# include "errors.h"
# include "env.h"

//	exec 	: execution type (logic or pipe)
//	size 	: size of the arrays
//	logic	: array of logic (and/or) for the cont (only applicable in logic)
//	type	: array of types of the cont
//	cont	: array of cont pointers

typedef struct s_token
{
	int		exec;
	size_t	size;
	int		*logic;
	int		*type;
	void	**cont;
}	t_token;

//	SHELL

int		exec_shell(t_token *tok, char **env);

//	CMD

int		exec_cmd(t_token *tok, char **env);

//	RED DIR

int		exec_reddir(t_token *tok);

//	RED DIR UTILS

int	red_open_file(char *filename, int flags, int mode);

int	red_cut_cont(t_token *tok, size_t i);

//	UTILS

size_t	exec_assign(t_token *tok, char ***env);

int		childreturn(int wstatus);

#endif
