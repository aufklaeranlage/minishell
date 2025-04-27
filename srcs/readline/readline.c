/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:17:27 by abronner          #+#    #+#             */
/*   Updated: 2025/04/26 16:30:48 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

extern char		**environ;

int	rl_tokenizer(char **line);

int	main(void)
{
	char	*buf;
	char	*exp;

	while (1)
	{
		buf = readline(RL_PROMPT);
		if (!buf || rl_tokenizer(&buf))
		{
			free(buf);
			continue ;
		}
		add_history(buf);
		exp = expander(buf, environ, 0);
		printf("buf: %s\n", buf);
		printf("exp: %s\n", exp);
		free(exp);
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

int	rl_tokenizer(char **line)
{
	size_t	i;

	i = 0;
	while (*line[i])
	{
		if (*line[i] == '\'' || *line[i] == '\"')
			i += rl_tokenquo(line, i);
//		else if (*line[i] == '<')
//			i += rl_tokenred(line);
		else
			++i;
	}
	return (0);
}

size_t	rl_tokenquo(char **line, size_t offset)
{
	size_t	i;
	char	q;

	q = *line[offset];
	i = 1;
	while (1)
	{
		if (!*line[offset + i] && !rl_appquo(line, q))
			break ;
		if (*line[offset + i] == q)
			break ;
	}
	return (i)
}
