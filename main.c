/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:28:54 by abronner          #+#    #+#             */
/*   Updated: 2025/06/17 16:39:05 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minichill.h"

// static char **ft_splitcpy(char **src);

int main(int ac, char **av, char **env)
{
    char        *buf;
    t_shell     *shell;
    (void)ac;
    (void)av;

    shell = malloc(sizeof(t_shell));
    shell->env = env_init((const char **)env);
    
    signal_handler_init();
    while (1)
    {
        buf = readline(RL_PROMPT);
        if (!buf)
            break;
        shell->cmd = malloc(sizeof(t_group));
        add_history(buf);
        if (create_execution_list(shell->cmd, buf, env) == 0)
        {
            //display groups partions
            // grouped_tokens_display(shell->cmd);
            g_signal = exec_wrapper(shell->cmd, shell->env);
        }
        else
            g_signal = 127; // ? IDK

        free(buf);
    }
    env_free(shell->env);
    return (0);
}

// static char **ft_splitcpy(char **src)
// {
// 	char	**ret;
// 	size_t	size;

// 	size = ft_splitcount((const char **)src);
// 	ret = ft_splitlcpy(src, size);
// 	return (ret);
// }
