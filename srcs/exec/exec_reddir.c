/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_reddir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:31:15 by abronner          #+#    #+#             */
/*   Updated: 2025/05/27 13:24:29 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	red_out(t_tokens *tok, int fd[2], size_t i);

static int	red_in(t_tokens *tok, int fd[2], size_t i);

static void	red_dup(int fd[2]);

int	exec_reddir(t_tokens *tok)
{
	size_t	i;
	int		fd[2];

	if (!tok)
		return (0);
	fd[0] = -1;
	fd[1] = -1;
	i = 0;
	while (i < tok->size)
	{
		if ((tok->type[i] == RED_IN || tok->type[i] == HERE_DOC)
			&& red_in(tok, fd, i))
			return (1);
		if ((tok->type[i] == RED_OUT || tok->type[i] == ADD_OUT)
			&& red_out(tok, fd, i))
			return (1);
		++i;
	}
	red_dup(fd);
	return (0);
}

//	red_in() opens a filedescriptor for either a file or a pipe to a child,
//	that will pass the contents of a 

static int	red_in(t_tokens *tok, int fd[2], size_t i)
{
	if (fd[0] != -1)
		close(fd[0]);
	if (tok->type[i] == RED_IN)
		fd[0] = open((char *)tok->content[i], O_RDONLY, NULL);
	else if (tok->type[i] == HERE_DOC)
		fd[0] = open_heredoc((char *)tok->content[i]);
	if (fd[0] == -1)
		return (errormsg((char *)tok->content[i], strerror(errno)), 1);
	return (0);
}

//	red_out() opens a filedescriptor with the appropriate flags based on the
//	redirection type and stores it in fd[1] to later be duped as stdout.

static int	red_out(t_tokens *tok, int fd[2], size_t i)
{
	int	flags;

	flags = 0;
	if (fd[1] != -1)
		close(fd[1]);
	if (tok->type[i] == RED_OUT)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	else if (tok->type[i] == ADD_OUT)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	fd[1] = open((char *)tok->content[i], flags, 0644);
	if (fd[1] == -1)
		return (errormsg((char *)tok->content[i], strerror(errno)), 1);
	return (0);
}

//	red_dup() checks if redirections got set and if they did, dups STDIN and
//	STDOUT respectively and closes the now obsolete file descriptors.

static void	red_dup(int fd[2])
{
	if (fd[0] != -1)
	{
		dup2(fd[0], STDIN);
		close(fd[0]);
	}
	if (fd[1] != -1)
	{
		dup2(fd[1], STDOUT);
		close(fd[1]);
	}
}
