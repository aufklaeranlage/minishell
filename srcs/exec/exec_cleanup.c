/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:31:00 by abronner          #+#    #+#             */
/*   Updated: 2025/07/04 16:30:36 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec_cleanup(t_shell *shell)
{
	if (!shell)
		return ;
	env_free(shell->env);
	shell->env = NULL;
	group_free(shell->cmd);
	shell->cmd = NULL;
}

void	group_free(t_group *grp)
{
	t_group	*tmp;

	while (grp)
	{
		token_free(grp->red);
		if (grp->data_type == SHELL)
			group_free((t_group *)grp->data);
		else
			token_free((t_tokens *)grp->data);
		tmp = grp;
		grp = grp->next;
		free(tmp);
	}
}

void	token_free(t_tokens *tok)
{
	if (!tok)
		return ;
	ft_freesplit(tok->content);
	free(tok->type);
	free(tok);
}
