/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:17:27 by abronner          #+#    #+#             */
/*   Updated: 2025/04/23 17:39:02 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

#ifndef RL_PROMPT
# define RL_PROMPT "minichill $>"
#endif

typedef struct s_rl
{
	int	dq;
	int	sq;
}	t_rl;

static char		*rl_getline(char *prompt);

static int	check_qoutes(char *line, t_rl *qoutes);

static char	*ft_strjoin(const char *s1, const char *s2);

int	main(void)
{
	char	*buf;
	char	*parsed;

	while (1)
	{
		buf = rl_getline(RL_PROMPT);
		add_history(buf);
		parsed = parser(buf);
		if (!strncmp(buf, "clear", 4))
			rl_clear_history();
		else if (!strncmp(buf, "display", 7))
			rl_redisplay();
		else if (!strncmp(buf, "eit", 4))
			break ;
		free(buf);
	}
	free(buf);
	rl_clear_history();
	return (0);
}

static char	*rl_getline(char *prompt)
{
	t_rl	qoute;
	char	*ret;
	char	*tmp;
	char	*buf;

	buf = readline(prompt);
	ret = strdup(buf);
	qoute.dq = 0;
	qoute.sq = 0;
	while (check_qoutes(buf, &qoute))
	{
		tmp = ft_strjoin(ret, "\n");
		free(buf);
		if (!tmp)
			return (free(ret), NULL);
		buf = rl_getline(">");
		if (!buf)
			return (free(tmp), free(ret), NULL);
		ret = ft_strjoin(tmp, buf);
		free(tmp);
	}
	free(buf);
	return (ret);
}

static int	check_qoutes(char *line, t_rl *qoutes)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\"')
		{
			if (qoutes->dq)
				qoutes->dq = 0;
			else
				qoutes->dq = 1;
		}
		else if (line[i] == '\'')
		{
			if (qoutes->sq)
				qoutes->sq = 0;
			else
				qoutes->sq = 1;
		}
		++i;
	}
	if (qoutes->dq || qoutes->sq)
		return (1);
	return (0);
}

static char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*out;
	size_t	len;

	len = strlen(s1) + strlen(s2) + 1;
	out = malloc(len-- * sizeof(char));
	if (!out)
		return (NULL);
	len = 0;
	while (*s1)
	{
		out[len] = *s1;
		++s1;
		++len;
	}
	while (*s2)
	{
		out[len] = *s2;
		++s2;
		++len;
	}
	out[len] = '\0';
	return (out);
}
