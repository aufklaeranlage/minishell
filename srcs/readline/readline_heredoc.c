/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:30:40 by abronner          #+#    #+#             */
/*   Updated: 2025/06/25 11:09:55 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

#ifndef HDEOF
# define HDEOF "here-document delimited by end-of-file"
#endif

static char	*heredoc_rec(const char *del, size_t dellen, size_t offset);

static char	*heredoc_retinit(size_t size);

//	Returns the lines read into readline as a string. each line is seperated
//	by a newline.

char	*rl_heredoc(const char *del)
{
	char	*ret;

	if (!del)
		return (NULL);
	ret = heredoc_rec(del, ft_strlen(del), 0);
	return (ret);
}

//	The recursive loop that makes up the main functionallity. Runs recursively
//	until the terminating conditon (line matches del with dellen) is met. Once
//	that condition is met the return is initialized and the readline buffers are
//	transfered into the combined string and freed.

static char	*heredoc_rec(const char *del, size_t dellen, size_t offset)
{
	char	*ret;
	char	*buf;
	size_t	buflen;

	buf = readline(HD_PROMPT);
	if (!buf)
		return (errormsg(SHNAME, "warning", HDEOF, NULL)
			, heredoc_retinit(offset + 1));
	buflen = ft_strlen(buf);
	if ((!ft_strncmp(buf, del, buflen) && buflen > 0))
	{
		ret = heredoc_retinit(offset + 1);
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

//	Initializes a string of the total length of size and terminates it at size.

static char	*heredoc_retinit(size_t size)
{
	char	*ret;

	ret = malloc(size-- * sizeof(*ret));
	if (ret)
		ret[size] = '\0';
	return (ret);
}
