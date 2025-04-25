/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:17:27 by abronner          #+#    #+#             */
/*   Updated: 2025/04/25 16:20:36 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static char		*rl_getline(char *prompt);

static char		*rl_multline(char *prompt);

static int		rl_check_qoutes(char *line, int *sq, int *dq);

extern char		**environ;

int	main(void)
{
	char	*buf;
	char	*exp;

	while (1)
	{
		buf = rl_getline(RL_PROMPT);
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

static char	*rl_getline(char *prompt)
{
	char	*ret;

	ret = rl_multline(prompt);
	if (!ret)
		return (NULL);
	return (ret);
}

static char	*rl_multline(char *prompt)
{
	char	*ret;
	char	*tmp;
	char	*buf;
	int		sq;
	int		dq;

	buf = readline(prompt);
	ret = strdup(buf);
	dq = 0;
	sq = 0;
	while (rl_check_qoutes(buf, &sq, &dq))
	{
		tmp = ft_strjoin(ret, "\n");
		free(buf);
		if (!tmp)
			return (free(ret), NULL);
		buf = readline(">");
		if (!buf)
			return (free(tmp), free(ret), NULL);
		free(ret);
		ret = ft_strjoin(tmp, buf);
		free(tmp);
	}
	free(buf);
	return (ret);
}

//	Basic syntax check that is run after reading any line.
//	Syntax errors:
//		Redirections:
//			Redirections followed by redirections or pipes.
//		Pipes:
//			Pipe symbols without non rediretion or pipe symbols.

static int	rl_check_qoutes(char *line, int *sq, int *dq)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\"' && !*sq)
		{
			if (*dq)
				*dq = 0;
			else
				*dq = 1;
		}
		else if (line[i] == '\'' && !*dq)
		{
			if (sq)
				*sq = 0;
			else
				*sq = 1;
		}
		++i;
	}
	if (*dq || *sq)
		return (1);
	return (0);
}
