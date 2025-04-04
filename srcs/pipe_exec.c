/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:39:44 by abronner          #+#    #+#             */
/*   Updated: 2025/04/03 23:19:58 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

static void	children(t_pipeutils *p_utils, int pipeid, char **env);

static void	pipe_exec_cmd(int pipeid, t_pipeutils *p_utils, char **env);

static char	*pipe_getexec(char *execname, char **paths);

int	main(int ac, char **av, char **env)
{
	t_pipeutils	p_utils;
	int			pipeid;
	size_t		i;

	p_utils.paths = ft_splitpaths((ft_getenv("PATH", env)));
	p_utils.cmd_count = pipe_countcmds(ac - 1, av + 1);
	p_utils.cmdargs = pipe_setcmdargs(ac - 1, av + 1, p_utils.cmd_count);
	p_utils.red_fd = -1;
	p_utils.red_type = 0;
	pipeid = pipe_chain(p_utils.cmd_count, p_utils.p_fd, &p_utils.pids);
	if (pipeid >= 0 && (size_t)pipeid < p_utils.cmd_count)
		children(&p_utils, pipeid, env);
	i = 0;
	while ((size_t)pipeid == p_utils.cmd_count && i < p_utils.cmd_count)
		waitpid(p_utils.pids[i++], NULL, 0);
	pipe_cleanup(pipeid, &p_utils);
}

static void	children(t_pipeutils *p_utils, int pipeid, char **env)
{
	pipe_red_check(pipeid, p_utils);
	pipe_connector(p_utils->p_fd, pipeid, p_utils->cmd_count - 1,
		p_utils->red_type);
	pipe_exec_cmd(pipeid, p_utils, env);
	pipe_closer(p_utils->p_fd, pipeid, p_utils->cmd_count - 1);
}

static void	pipe_exec_cmd(int pipeid, t_pipeutils *p_utils, char **env)
{
	char	*exec;

	if (!p_utils->cmdargs)
		return ;
	exec = pipe_getexec(p_utils->cmdargs[pipeid][0], p_utils->paths);
	if (exec)
		execve(exec, p_utils->cmdargs[pipeid], env);
	execve(p_utils->cmdargs[pipeid][0], p_utils->cmdargs[pipeid], env);
	if (pipeid)
		pipe_errormsg("Command not found", p_utils->cmdargs[pipeid][0], p_utils->pids[pipeid - 1]);
	else
		pipe_errormsg("Command not found", p_utils->cmdargs[pipeid][0], -1);
	pipe_cleanup(pipeid, p_utils);
	free(exec);
	exit(127);
}

static char	*pipe_getexec(char *execname, char **paths)
{
	char	*exec;
	char	*tmp;
	size_t	i;

	tmp = ft_strjoin("/", execname);
	if (!tmp)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		exec = ft_strjoin(paths[i], tmp);
		if (!exec)
			return (free(tmp), NULL);
		if (access(exec, F_OK | X_OK) == 0)
			return (free(tmp), exec);
		free(exec);
		++i;
	}
	return (NULL);
}
