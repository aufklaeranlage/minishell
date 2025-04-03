/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:39:44 by abronner          #+#    #+#             */
/*   Updated: 2025/04/03 18:46:36 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

static void	children(t_pipeutils *p_utils, int pipeid);

int	main(int ac, char **av, char **env)
{
	t_pipeutils	p_utils;
	int			pipeid;

	p_utils.paths = ft_splitpaths((ft_getenv("PATH", env)));
	p_utils.cmd_count = pipe_countcmds(ac - 1, av + 1);
	p_utils.cmdargs = pipe_setcmdargs(ac - 1, av + 1, p_utils.cmd_count);
	p_utils.red_fd = -1;
	p_utils.red_type = 0;
	pipeid = pipe_chain(p_utils.cmd_count, p_utils.p_fd, &p_utils.pids);
	if (pipeid >= 0 && (size_t)pipeid < p_utils.cmd_count)
		children(&p_utils, pipeid);
	pipe_cleanup(pipeid, &p_utils);
}

static void	children(t_pipeutils *p_utils, int pipeid)
{
	pipe_red_check(pipeid, p_utils);
	pipe_connector(p_utils->p_fd, pipeid, p_utils->cmd_count - 1,
		p_utils->red_type);
	pipe_closer(p_utils->p_fd, pipeid, p_utils->cmd_count - 1);
}
