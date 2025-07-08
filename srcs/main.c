/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:28:54 by abronner          #+#    #+#             */
/*   Updated: 2025/07/05 16:32:32 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "inbuilds.h"
#include "minichill.h"

static void	shellassign(t_group *grp, t_shell *shell);

static void	do_dirt(t_shell *shell);

int	main(int ac, char **av, char **env)
{
	t_shell		shell;

	(void)ac;
	(void)av;
	shell.env = env_init((const char **)env);
	shell.cmd = NULL;
	signal_handler_init();
	do_dirt(&shell);
	env_free(shell.env);
	return (0);
}

static void	shellassign(t_group *grp, t_shell *shell)
{
	while (grp)
	{
		grp->shell = shell;
		if (grp->data_type == SHELL)
			shellassign((t_group *)grp->data, shell);
		grp = grp->next;
	}
}

static void	do_dirt(t_shell *shell)
{
	char	*prompt;
	char	*buf;

	while (1)
	{
		signal_handler_init();
		prompt = construct_prompt(shell->env);
		buf = readline(prompt);
		free(prompt);
		if (!buf)
			ft_exit_ctrld(shell);
		shell->cmd = ft_calloc(1, sizeof(t_group));
		add_history(buf);
		if (create_execution_list(shell, buf) == 0)
		{
			shellassign(shell->cmd, shell);
			shell->env->status = exec_shell(shell->cmd, shell->env);
			if (g_signal >= 130 && g_signal <= 131)
				shell->env->status = g_signal;
		}
		group_free(shell->cmd);
		shell->cmd = NULL;
		free(buf);
	}
}
