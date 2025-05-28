/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:30:40 by abronner          #+#    #+#             */
/*   Updated: 2025/05/28 16:47:51 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static char	*heredoc_rec(char *del, size_t dellen, size_t offset);

char	*rl_heredoc(char *del)
{
	char	*ret;
	size_t	len;

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
		return (NULL);
	buflen = ft_strlen(buf);
	if (!ft_strncmp(buf, del, buflen) && buflen > 0)
	{
		ret = malloc((offset + 1) * sizeof(*ret));
		if (ret)
			ret[offset] = '\0';
		return (free(buf), ret);
	}
	else
	{
		ret = heredoc_rec(del, dellen, offset + buflen + 1);
	}
	if (!ret)
		return (free(buf), NULL);
	ft_strncpy(ret + offset, buf, buflen);
	ret[offset + buflen] = '\n';
	free(buf);
	return (ret);
}
