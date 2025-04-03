/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_red.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:15:08 by abronner          #+#    #+#             */
/*   Updated: 2025/04/03 15:40:22 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

static void	pipe_red_store(int pipeid, t_pipeutils *p_utils);

static int	pipe_red_infile(int pipeid, t_pipeutils *p_utils, size_t argindex);

void	pipe_red_check(int pipeid, t_pipeutils *p_utils)
{
	char	*tmp;

	tmp = ft_getenv("<", p_utils->cmdargs[pipeid]);
	while (tmp)
	{
		pipe_red_store(pipeid, p_utils);
		tmp = ft_getenv("<", p_utils->cmdargs[pipeid]);
	}
}

static void	pipe_red_store(int pipeid, t_pipeutils *p_utils)
{
	size_t	i;
	int		ret;

	i = 0;
	while (!(!ft_strncmp("<", p_utils->cmdargs[pipeid][i], 1) ||
		!ft_strncmp(">", p_utils->cmdargs[pipeid][i], 1)))
		++i;
//	if (ft_strncmp("<<", p_utils->cmdargs[pipeid][i], 2))
//		red_info.red_type = HERE_DOC;
	if (!ft_strncmp("<", p_utils->cmdargs[pipeid][i], 1))
		ret = pipe_red_infile(pipeid, p_utils, i);
//	else if (ft_strncmp(">>", p_utils->cmdargs[pipeid][i], 2))
//		red_info.red_type = APPEND;
//	else if (ft_strncmp(">", p_utils->cmdargs[pipeid][i], 1))
//		red_info.red_type = OUTFILE;
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
	return (0);
}
