/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:31:00 by abronner          #+#    #+#             */
/*   Updated: 2025/06/12 10:59:48 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	token_free(t_tokens *tok);

void	exec_cleanup(t_shell *shell)
{
	env_free(shell->env);
	shell->env = NULL;
	group_free(shell->cmd);
	shell->cmd = NULL;
	free(shell);
}

void	group_free(t_group *grp)
{
	t_group	*tmp;

	while (grp)
	{
		token_free(grp->red);
		if (grp->exec_type == PIPE || grp->data_type == GROUP)
			group_free((t_group *)grp->data);
		else
			token_free((t_tokens *)grp->data);
		tmp = grp;
		grp = grp->next;
		free(tmp);
	}
}

static void	token_free(t_tokens *tok)
{
	if (!tok)
		return ;
	ft_freesplit(tok->content);
	free(tok->type);
	free(tok);
}
