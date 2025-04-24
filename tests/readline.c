/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:17:27 by abronner          #+#    #+#             */
/*   Updated: 2025/04/24 17:34:18 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

#ifndef RL_PROMPT
# define RL_PROMPT "minichill $>"
#endif

char	**split_line_to_tokens(char *str);

static char		*rl_getline(char *prompt);

static char		*rl_multline(char *prompt);

static int		rl_check_qoutes(char *line, int *sq, int *dq);

static char		*ft_strjoin(const char *s1, const char *s2);

int	main(void)
{
	char	*buf;

	while (1)
	{
		buf = rl_getline(RL_PROMPT);
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

static char	*rl_getline(char *prompt)
{
	char	*ret;
	char	**out;

	ret = rl_multline(prompt);
	if (!ret)
		return (NULL);
	out = split_line_to_tokens(ret);
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
/*
static int	rl_check_syntax(char *line)
{
	
}
*/
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
/*
static char	*rl_heredoc(char *line)
{

}

static char	*rl_checkheredoc(char *line)
*/
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

char **split_line_to_tokens(char *str)
{
    size_t i = 0;
	size_t j = 0;
    char **out;
    char *tmp = malloc(strlen(str) * 3 + 1);
    if (!tmp)
        return (NULL);
    while (str[i])
    {
        char curr = str[i];
        char next = str[i + 1];
        if (next && (curr == '|' || curr == '&' || curr == '>' || curr == '<'))
        {
            tmp[j++] = ' ';
            tmp[j++] = curr;
            if (next == curr)
            {
                tmp[j++] = curr;
                i++;
            }
            tmp[j++] = ' ';
        }
        else
            tmp[j++] = curr;
        i++;
    }
    tmp[j] = '\0';
    out = NULL;
    free(tmp);
    return (out);
}
