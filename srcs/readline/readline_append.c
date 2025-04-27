/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_append.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:07:16 by abronner          #+#    #+#             */
/*   Updated: 2025/04/26 16:16:45 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static char	*appdel_rec(char *del, size_t dellen, size_t offset);

static char	*appqou_rec(char quote, size_t offset);

//	rl_appdel reads from readline until a line that matches the delimiter
//	string is found. Once the delimiter is found it creates a new string
//	with the combined total length of the original *line string and all the
//	lines inputted. The inputted lines will be copied into the string one by
//	one and finally the newly created string is put into the position the
//	original string was stored in.

int	rl_appdel(char **line, char *del)
{
	char	*ret;
	size_t	len;
	
	if (!line || !*line || !del)
		return (1);
	len = ft_strlen(*line);
	ret = appdel_rec(del, ft_strlen(del), len);
	if (!ret)
		return (1);
	ft_strncpy(ret, line, len);	
	free(*line);
	*line = ret;
	return (0);
}

static char	*appdel_rec(char *del, size_t dellen, size_t offset)
{
	char	*ret;
	char	*buf;
	size_t	buflen;

	buf = readline(">");
	if (!buf)
		return (NULL);
	buflen = ft_strlen(buf);
	if (!ft_strncmp(buf, del, dellen) && buf[dellen] == '\n')
	{
		ret = malloc((offset + buflen + 1) * sizeof(ret));
		ret[offset + buflen] = '\0';
	}
	else
		ret = appdel_rec(del, dellen, offset + buflen);
	if (!ret)
		return (free(buf), NULL);
	ft_strncpy(ret + offset, buf, buflen);
	free(buf);
	return (ret);
}

//	rl_appquo reads from readline until a line that contains the character
//	specified in quote is found. Once the character is found it creates a new
//	string with the combined total length of the original *line string and all
//	the lines inputted. The inputted lines will be copied into the string one
//	by one and finally the newly created string is put into the position the
//	original string was stored in.

int	rl_appquote(char **line, char quote)
{
	char	*ret;
	size_t	len;
	
	if (!line || !*line)
		return (1);
	len = ft_strlen(*line);
	ret = appquo_rec(quote, len);
	if (!ret)
		return (1);
	ft_strncpy(ret, line, len);	
	free(*line);
	*line = ret;
	return (0);
}

static char	*appqou_rec(char quote, size_t offset)
{
	char	*ret;
	char	*buf;
	size_t	buflen;

	buf = readline(">");
	if (!buf)
		return (NULL);
	buflen = ft_strlen(buf);
	if (ft_strchr(buf, quote))
	{
		ret = malloc((offset + buflen + 1) * sizeof(ret));
		ret[offset + buflen] = '\0';
	}
	else
		ret = appquo_rec(quote, offset + buflen);
	if (!ret)
		return (free(buf), NULL);
	ft_strncpy(ret + offset, buf, buflen);
	free(buf);
	return (ret);
}
