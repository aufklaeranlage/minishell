/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:29:52 by abronner          #+#    #+#             */
/*   Updated: 2025/05/13 11:48:27 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

size_t	exec_assign(t_token *tok, char ***env)
{
	size_t	i;

	i = 0;
	while (i < tok->size && tok->type == ASSIGN)
	{
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
