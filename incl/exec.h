/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:30:49 by abronner          #+#    #+#             */
/*   Updated: 2025/05/13 11:30:37 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "stdlib.h"

# include "pipe.h"
# include "errors.h"

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

//	UTILS

size_t	exec_assign(t_token *tok, char ***env);

int		childreturn(int wstatus);

#endif
