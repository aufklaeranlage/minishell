/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_red.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:15:08 by abronner          #+#    #+#             */
/*   Updated: 2025/04/03 18:47:57 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

static int	pipe_red_infile(int pipeid, t_pipeutils *p_utils, size_t argindex);

static int	pipe_red_append(int pipeid, t_pipeutils *p_utils, size_t argindex);

static int	pipe_red_trunc(int pipeid, t_pipeutils *p_utils, size_t argindex);

static int	pipe_red_heredoc(int pipeid, t_pipeutils *p_utils, size_t argindex);

static void	pipe_red_heredoc_loop(char *delim, int write_fd);

int	pipe_red_check(int pipeid, t_pipeutils *p_utils)
{
	size_t	i;
	size_t	len;
	int		ret;

	len = ft_splitcount((const char **)p_utils->cmdargs[pipeid]);
	ret = 0;
	while (!ret)
	{
		i = 0;
		while (i + 1 < len && !(!ft_strncmp("<", p_utils->cmdargs[pipeid][i], 1) ||
			!ft_strncmp(">", p_utils->cmdargs[pipeid][i], 1)))
			++i;
		if (i + 1 == len)
			break ;
		if (!ft_strncmp("<<", p_utils->cmdargs[pipeid][i], 2))
			ret = pipe_red_heredoc(pipeid, p_utils, i);
		else if (!ft_strncmp("<", p_utils->cmdargs[pipeid][i], 1))
			ret = pipe_red_infile(pipeid, p_utils, i);
		else if (!ft_strncmp(">>", p_utils->cmdargs[pipeid][i], 2))
			ret = pipe_red_append(pipeid, p_utils, i);
		else if (!ft_strncmp(">", p_utils->cmdargs[pipeid][i], 1))
			ret = pipe_red_trunc(pipeid, p_utils, i);
	}
	return (ret);
}

static int	pipe_red_infile(int pipeid, t_pipeutils *p_utils, size_t argindex)
{
	char	*filename;
	size_t	len;

	len = ft_strlen(p_utils->cmdargs[pipeid][argindex]);
	if (len == 1)
		filename = p_utils->cmdargs[pipeid][argindex + 1];
	else
		filename = p_utils->cmdargs[pipeid][argindex] + 1;
	if (p_utils->red_fd != -1)
		close(p_utils->red_fd);
	p_utils->red_fd = open(filename, O_RDONLY);
	if (p_utils->red_fd == -1)
	{
		if (pipeid)
			pipe_errormsg(strerror(errno), filename, p_utils->pids[pipeid - 1]);
		else
			pipe_errormsg(strerror(errno), filename, -1);
		pipe_cleanup(pipeid, p_utils);
		exit(1);
	}
	dup2(p_utils->red_fd, STDIN_FILENO);
	if (pipe_red_cutcmd(p_utils->cmdargs + pipeid, argindex, 1 + len > 1))
		return (1);
	p_utils->red_type = RED_IN;
	return (0);
}

static int	pipe_red_append(int pipeid, t_pipeutils *p_utils, size_t argindex)
{
	char	*filename;
	size_t	len;

	len = ft_strlen(p_utils->cmdargs[pipeid][argindex]);
	if (len == 2)
		filename = p_utils->cmdargs[pipeid][argindex + 1];
	else
		filename = p_utils->cmdargs[pipeid][argindex] + 1;
	if (p_utils->red_fd != -1)
		close(p_utils->red_fd);
	p_utils->red_fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (p_utils->red_fd == -1)
	{
		if (pipeid)
			pipe_errormsg(strerror(errno), filename, p_utils->pids[pipeid - 1]);
		else
			pipe_errormsg(strerror(errno), filename, -1);
		pipe_cleanup(pipeid, p_utils);
		exit(1);
	}
	dup2(p_utils->red_fd, STDOUT_FILENO);
	if (pipe_red_cutcmd(p_utils->cmdargs + pipeid, argindex, 1 + len > 2))
		return (1);
	p_utils->red_type = RED_OUT;
	return (0);
}

static int	pipe_red_trunc(int pipeid, t_pipeutils *p_utils, size_t argindex)
{
	char	*filename;
	size_t	len;

	len = ft_strlen(p_utils->cmdargs[pipeid][argindex]);
	if (len == 1)
		filename = p_utils->cmdargs[pipeid][argindex + 1];
	else
		filename = p_utils->cmdargs[pipeid][argindex] + 1;
	if (p_utils->red_fd != -1)
		close(p_utils->red_fd);
	p_utils->red_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (p_utils->red_fd == -1)
	{
		if (pipeid)
			pipe_errormsg(strerror(errno), filename, p_utils->pids[pipeid - 1]);
		else
			pipe_errormsg(strerror(errno), filename, -1);
		pipe_cleanup(pipeid, p_utils);
		exit(1);
	}
	dup2(p_utils->red_fd, STDOUT_FILENO);
	if (pipe_red_cutcmd(p_utils->cmdargs + pipeid, argindex, 1 + len > 1))
		return (1);
	p_utils->red_type = RED_OUT;
	return (0);
}

static int	pipe_red_heredoc(int pipeid, t_pipeutils *p_utils, size_t argindex)
{
	size_t	len;
	char	*delim;
	int		p_fd[2];
	int		pid;

	len = ft_strlen(p_utils->cmdargs[pipeid][argindex]);
	if (len == 2)
		delim = p_utils->cmdargs[pipeid][argindex + 1];
	else
		delim = p_utils->cmdargs[pipeid][argindex] + 2;
	pipe(p_fd);
	pid = fork();
	if (pid)
	{
		close(p_fd[0]);
		if (pipeid)
			close(p_utils->p_fd[0]);
		close(p_utils->p_fd[1]);
		pipe_red_heredoc_loop(delim, p_fd[1]);
		pipe_cleanup(pipeid, p_utils);
		waitpid(pid, NULL, 0);
		exit(1);
	}
	else
	{
		dup2(p_fd[0], STDIN_FILENO);
		close(p_fd[1]);
		if (pipeid)
			close(p_utils->p_fd[0]);
	}
	if (pipe_red_cutcmd(p_utils->cmdargs + pipeid, argindex, 1 + len > 2))
		return (1);
	p_utils->red_type = RED_OUT;
	return (0);
}

static void	pipe_red_heredoc_loop(char *delim, int write_fd)
{
	char	*line;
	size_t	line_len;

	while (1)
	{
		ft_putstr_fd(HERE_DOC_MSG, STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (line)
			line_len = ft_strlen(line);
		if (!line || (delim && !ft_strncmp(line, delim, line_len - 1)))
			break ;
		ft_putstr_fd(line, write_fd);
		free(line);
	}
	free(line);
	close(write_fd);
	line = get_next_line(write_fd);
}
