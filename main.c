/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:28:54 by abronner          #+#    #+#             */
/*   Updated: 2025/06/24 10:48:11 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minichill.h"

// static char **ft_splitcpy(char **src);

static void	shellassign(t_group *grp, t_shell *shell);

int main(int ac, char **av, char **env)
{
	char		*prompt;
    char        *buf;
    t_shell     *shell;
    (void)ac;
    (void)av;

    shell = malloc(sizeof(t_shell));
    shell->env = env_init((const char **)env);
    
    signal_handler_init();
    while (1)
    {
		prompt = construct_prompt(shell->env);
        buf = readline(prompt);
		free(prompt);
        if (!buf)
            break;
        shell->cmd = malloc(sizeof(t_group));
        add_history(buf);
        if (create_execution_list(shell->cmd, buf, env) == 0)
        {
			shellassign(shell->cmd, shell);
            //display groups partions
            // grouped_tokens_display(shell->cmd);
            g_signal = exec_first(shell->cmd, shell->env);
			group_free(shell->cmd);
        }
        else
			errormsg(SHNAME, "toks", "couldn't create grps", NULL);

        free(buf);
    }
    env_free(shell->env);
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
// static char **ft_splitcpy(char **src)
// {
// 	char	**ret;
// 	size_t	size;

// 	size = ft_splitcount((const char **)src);
// 	ret = ft_splitlcpy(src, size);
// 	return (ret);
// }
