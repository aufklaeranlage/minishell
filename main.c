/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:28:54 by abronner          #+#    #+#             */
/*   Updated: 2025/06/01 22:45:53 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minichill.h"

static char **ft_splitcpy(char **src);

int main(int ac, char **av, char **env)
{
    char        *buf;
    char        **local_env;
    (void)ac;
    (void)av;
    local_env = ft_splitcpy(env);
    
    signal_handler_init();
    while (1)
    {
        buf = readline(RL_PROMPT);
        if (!buf)
            break;
        t_group *group = malloc(sizeof(t_group));
        add_history(buf);
        create_execution_list(group, buf, local_env);
        //display groups partions
        // grouped_tokens_display(group);

		exec_wrapper(group, &env);
        
        free(buf);
    }
    ft_freesplit(local_env);
    return (0);
}

static char **ft_splitcpy(char **src)
{
	char	**ret;
	size_t	size;

	size = ft_splitcount((const char **)src);
	ret = ft_splitlcpy(src, size);
	return (ret);
}
