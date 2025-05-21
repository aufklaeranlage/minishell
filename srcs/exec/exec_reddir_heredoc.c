/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_reddir_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:28:07 by abronner          #+#    #+#             */
/*   Updated: 2025/05/21 11:33:06 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*red_gettmpfilename(void);

int	open_heredoc(char *hd_str)
{
	char	*filename;
	int		fd;

	filename = red_gettmpfilename();
	if (!filename)
		return (1);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (free(filename), 1);
	ft_putstr_fd(hd_str, fd);
	close(fd);
	fd = open(filename, O_RDONLY, 0);
	unlink(filename);
	free(filename);
	return (fd);
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
