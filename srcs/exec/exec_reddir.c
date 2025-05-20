/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_reddir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:31:15 by abronner          #+#    #+#             */
/*   Updated: 2025/05/20 14:15:07 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	red_out(t_token *tok, int fd[2], size_t i);

static void	red_in(t_token *tok, int fd[2], size_t i);

static int	open_heredoc(char *hd_str);

static char	*red_gettmpfilename(void);

int	exec_reddir(t_token *tok)
{
	size_t	i;
	int		fd[2];

	bzero(fd, 2 * sizeof(fd));
	i = 0;
	while (i < tok->size)
	{
		if ((tok->type == RED_IN || tok->type == HERE_DOC))
			if (red_in(tok, fd, i))
				return (1);
		if ((tok->type == RED_OUT || tok->type == APP_OUT))
			if (red_out(tok, fd, i))
				return (1);
		++i;
	}
	dup2(fd[0], STDIN);
	dup2(fd[1], STDOUT);
	return (0);
}

//	red_in() opens a filedescriptor for either a file or a pipe to a child,
//	that will pass the contents of a 

static int	red_in(t_token *tok, int fd[2], size_t i)
{
	if (fd[0])
		close(fd[0]);
	if (tok->type[i] == RED_IN)
		fd[0] = open((char *)tok->cont[i], O_RDONLY, NULL);
	else if (tok->type == HERE_DOC)
		fd[0] = open_heredoc((char *)tok->cont[i]);
	if (fd[0] == -1)
		return (errormsg((char *)tok->cont[i], strerror(errno)), 1);
	return (0);
}

static int	open_heredoc(char *hd_str)
{
	char	*filename;
	int		fd;
	
	filename = red_gettmpfilename();
	if (!filename)
		return (1);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (free(filename), 1);
	ft_putstr_fd(fd, hd_str);
	close(fd);
	fd = open(filename, O_RDONLY, 0);
	if (!fd)
		return (free(filename), 1);
	unlink(filename);
	free(filename);
	return (fd);
}

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
	while (i < 10)
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

//	red_out() opens a filedescriptor with the appropriate flags based on the
//	redirection type and stores it in fd[1] to later be duped as stdout.

static int	red_out(t_token *tok, int fd[2], size_t i)
{
	int	flags;

	if (fd[1] && fd[1] != -1)
		close(fd[1]);
	if (tok->type[i] == RED_OUT)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	else if (tok->type[i] == ADD_OUT)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	fd[1] = open((char *)tok->cont[i], flags, 0644);
	if (!fd[1])
		return (errormsg((char *)tok->cont[i], strerror(errno)), 1);
	return (0);
}
