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

#include "libft_put.h"
#include "readline.h"
#include "tokenisation.h"

#ifndef HDEOF
# define HDEOF "here-document delimited by end-of-file"
#endif

static char	*red_gettmpfilename(void);

static char	*heredoc_rec(const char *del, size_t dellen, size_t offset);

static char	*heredoc_retinit(size_t size);

//	Returns the lines read into readline as a string. each line is seperated
//	by a newline.

char	*rl_heredoc(const char *del, t_env *env)
{
	char	*ret;
	char	*expdel;
	char	*str;
	int		fd;

	if (!del)
		return (NULL);
	ret = red_gettmpfilename();
	fd = open(ret, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (free(ret), NULL);
	expdel = get_expandet((char *)del, env);
	str = heredoc_rec(expdel, ft_strlen(expdel), 0);
	free(expdel);
	if (str && (ft_strchr(del, '\'') || ft_strchr(del, '"')))
		ft_putstr_fd(str, fd);
	else if (str)
	{
		expdel = get_expandet(str, env);
		ft_putstr_fd(expdel, fd);
		free(expdel);
	}
	free(str);
	return (ret);
}

//	red_gettmpfilename() creates a file in /tmp and returns the name of that
//	file. The file is supposed to be used as a temporary file (f.e. open with
//	write and read permissions and close it after writing to it, only to open
//	it up again (resetting the file position) and unlinking it afterwards).
//	The files created have a max name length of 10 and each characters can hold
//	one of 96 different values. That leads to 6.64832636×10¹⁹ different
//	potential file names.

static char	*red_gettmpfilename(void)
{
	char	*ret;
	size_t	i;
	size_t	c;

	ret = malloc(16 * sizeof(*ret));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, "/tmp/", 16);
	i = 5;
	while (i < 15)
	{
		c = 32;
		while (c < 128)
		{
			ret[i] = c;
			if (access(ret, F_OK) == -1)
				return (ret);
			++c;
		}
		++i;
	}
	return (free(ret), NULL);
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
	if ((!ft_strncmp(buf, del, dellen + 1) && buflen > 0))
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
