/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:39:05 by abronner          #+#    #+#             */
/*   Updated: 2025/04/14 09:54:01 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

static int	pipe_init(pid_t **pids, int chainlinks);

static void	pipe_plumber(int i, int chainlinks, int p_fd[2], int tp_fd[2]);

/*	pip_chain initializes a number of children indicated by chainlinks. The
 *	parent process does not become part of the chain. It is merely responisble
 *	handling the opening, sorting and closing of the pipefds as well as
 *	collecting the process id's of the children created by pipe_chain in pids.
 *	If no array of pid_t's was provided the function will ignore it and still
 *	create the chain.
 *	Each part of the chain, including the parent will recieve a pipeid. The
 *	pipeid starts counting at 0 for the parent. From there on the children will
 *	start at 1 up to chainlink. The lower children will have a pipe with the
 *	write end leading to the next higher numbered child and a read pipe to the
 *	next lower child.
 *	Returns -1 on chainlinks being less than 2 or not being able to malloc for
 *	the array of pids.
 */

int	pipe_chain(int chainlinks, int p_fd[2], pid_t **pids)
{
	int	pid;
	int	tp_fd[2];
	int	i;

	if (pipe_init(pids, chainlinks))
		return (-1);
	ft_bzero(p_fd, 2 * sizeof(*p_fd));
	pid = 1;
	i = 0;
	while (i < chainlinks && pid)
	{
		pipe_plumber(i, chainlinks, p_fd, tp_fd);
		pid = fork();
		if (!pid)
			break ;
		if (pids)
			(*pids)[i] = pid;
		++i;
	}
	if (i + 1 < chainlinks || i == chainlinks)
		close(tp_fd[0]);
	return (i);
}

/*	Checks for proper chainlink length and if pids needs to be malloced.
 *	Returns -1 on chainlinks being less than 2 or not being able to malloc for
 *	pids.
 */

static int	pipe_init(pid_t **pids, int chainlinks)
{
	if (chainlinks < 2)
		return (-1);
	if (pids != NULL)
	{
		*pids = malloc(chainlinks * sizeof(**pids));
		if (pids == NULL)
			return (-1);
	}
	return (0);
}

/*	pipe_plumber connects the main pipe p_fd by using the data stored in
 *	tp_fd and closes the fds that become obsolete to the parent process
 *	after the child with the read or write end of the pipe already split off.
*/

static void	pipe_plumber(int i, int chainlinks, int p_fd[2], int tp_fd[2])
{
	if (i)
	{
		close(p_fd[1]);
		if (i > 1)
			close(p_fd[0]);
		p_fd[0] = tp_fd[0];
	}
	if (i + 1 < chainlinks)
	{
		pipe(tp_fd);
		p_fd[1] = tp_fd[1];
	}
}

/*	pipe_connector connects the write and read ends of the children in a pipe
 *	chain by duping the write end with STDOUT and their read end with STDIN.
 *	The first child in the chain only has an open read end and will not dup the
 *	unset write and, the last child in the chain only has an open write end and
 *	will not dup their usnet read end.
*/

void	pipe_connector(int p_fd[2], int pipeid, int max_pipeid, t_pipeutils *p_utils)
{
	if (pipeid < max_pipeid)
	{
		if (!(p_utils->red_type & RED_OUT))
			dup2(p_fd[1], STDOUT_FILENO);
		else
			dup2(p_utils->red_fd[1], STDOUT_FILENO);
	}
	if (pipeid && pipeid <= max_pipeid)
	{
		if (!(p_utils->red_type & RED_IN))
			dup2(p_fd[0], STDIN_FILENO);
		else
			dup2(p_utils->red_fd[0], STDIN_FILENO);
	}
}

void	pipe_closer(int p_fd[2], int pipeid, int max_pipeid)
{
	if (pipeid < max_pipeid)
		close(p_fd[1]);
	if (pipeid && pipeid <= max_pipeid)
		close(p_fd[0]);
}
