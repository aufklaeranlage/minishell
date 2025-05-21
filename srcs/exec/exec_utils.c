/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:29:52 by abronner          #+#    #+#             */
/*   Updated: 2025/05/20 16:23:03 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

size_t	exec_assign(t_token *tok, char ***env)
{
	size_t	i;

	i = 0;
	while (i < tok->size && tok->type == ASSIGN)
	{
		//	ASSIGN ENV
		++i;
	}
	return (i);
}

int	childreturn(int wstatus)
{
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	if (WIFSIGNALED(wstatus))
		return (WTERMSIG(wstatus));
	return (-1);
}
