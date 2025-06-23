/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_append.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:07:16 by abronner          #+#    #+#             */
/*   Updated: 2025/06/23 12:55:54 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

#ifndef APPER
# define APPERR "Couldn't append heredoc to readline"
#endif

//	Wrapper function for rl_heredoc that also appends the result and delimiter
//	to the readline buffer that can be stored in memory.
//	EXPERIMENTAL USE!

char	*rl_hdapp(const char *del, char **line)
{
	char	*ret;
	char	*newline;
	size_t	sizes[3];
	size_t	size;
	size_t	pos;

	ret = rl_heredoc(del);
	if (!ret)
		return (NULL);
	sizes[0] = ft_strlen(*line) + 1;
	sizes[1] = ft_strlen(ret) + 1;
	sizes[2] = ft_strlen(del) + 1;
	size = sizes[0] + sizes[1] + sizes[2];
	newline = malloc(size-- * sizeof(*newline));
	if (!newline)
		return (errormsg(SHNAME, "heredoc", APPERR, NULL), ret);
	newline[size] = '\0';
	pos = ft_strlcpy(newline, *line, sizes[0]);
	newline[pos++] = '\n';
	pos += ft_strlcpy(newline + pos, ret, sizes[1]);
	newline[pos++] = '\n';
	pos += ft_strlcpy(newline + pos, del, sizes[2]);
	free(*line);
	*line = newline;
	return (ret);
}
