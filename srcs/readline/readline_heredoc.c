/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:30:40 by abronner          #+#    #+#             */
/*   Updated: 2025/06/06 15:24:48 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static char	*heredoc_rec(char *del, size_t dellen, size_t offset);

static char	*heredoc_retinit(size_t size);

char	*rl_heredoc(char *del)
{
	char	*ret;

	if (!del)
		return (NULL);
	ret = heredoc_rec(del, ft_strlen(del), 0);
	return (ret);
}

static char	*heredoc_rec(char *del, size_t dellen, size_t offset)
{
	char	*ret;
	char	*buf;
	size_t	buflen;

	buf = readline(HD_PROMPT);
	if (!buf)
		return (errormsg("warning", "here-document delimited by end-of-file")
			, heredoc_retinit(offset));
	buflen = ft_strlen(buf);
	if ((!ft_strncmp(buf, del, buflen) && buflen > 0))
	{
		ret = heredoc_retinit(offset);
		return (free(buf), ret);
	}
	else
		ret = heredoc_rec(del, dellen, offset + buflen + 1);
	if (!ret)
		return (free(buf), NULL);
	ft_strncpy(ret + offset, buf, buflen);
	ret[offset + buflen] = '\n';
	free(buf);
	return (ret);
}

static char	*heredoc_retinit(size_t size)
{
	char	*ret;

	ret = malloc((size + 1) * sizeof(*ret));
	if (ret)
		ret[size] = '\0';
	return (ret);
}
