/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:17:27 by abronner          #+#    #+#             */
/*   Updated: 2025/04/23 13:28:29 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

#ifndef RL_PROMPT
# define RL_PROMPT "minichill $>"
#endif

int	main(void)
{
	char	*buf;

	while (1)
	{
		buf = readline(RL_PROMPT);
		add_history(buf);
		if (!strncmp(buf, "clear", 4))
			rl_clear_history();
		else if (!strncmp(buf, "display", 7))
			rl_redisplay();
		else if (!strncmp(buf, "exit", 4))
			break ;
		free(buf);
	}
	free(buf);
	rl_clear_history();
	return (0);
}
