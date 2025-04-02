/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:39:44 by abronner          #+#    #+#             */
/*   Updated: 2025/04/02 16:19:36 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

static int	pipe_countcmds(int ac, char **av);

static char	***pipe_setcmdargs(int ac, char **av, int cmd_count);

static void	free_cmdargs(char ***cmdargs);

int	main(int ac, char **av, char **env)
{
	t_executils	eutils;
	int			p_fd[2];
	int			*pids;
	int			pipeid;

	eutils.paths = ft_splitpaths((ft_getenv("PATH", env)));
	eutils.cmd_count = pipe_countcmds(ac - 1, av + 1);
	eutils.cmdargs = pipe_setcmdargs(ac - 1, av + 1, eutils.cmd_count);
	pipeid = pipe_chain(eutils.cmd_count, p_fd, &pids);
	pipe_connector(p_fd, pipeid, eutils.cmd_count);
	pipe_closer(p_fd, pipeid, eutils.cmd_count);
	free_cmdargs(eutils.cmdargs);
	ft_freesplit(eutils.paths);
	free(pids);
}

static int	pipe_countcmds(int ac, char **av)
{
	int		cmd_count;
	size_t	i;

	cmd_count = 1;
	i = 0;
	while (i < (size_t)ac)
	{
		if (!ft_strncmp(av[i], "|\0", 2))
			++cmd_count;
		++i;
	}
	return (cmd_count);
}

static char	***pipe_setcmdargs(int ac, char **av, int cmd_count)
{
	char	***ret;
	size_t	i;
	size_t	j;
	size_t	k;

	ret = malloc((cmd_count + 1) * sizeof(*ret));
	if (!ret)
		return (NULL);
	ret[cmd_count] = NULL;
	i = 0;
	j = 0;
	while (i < (size_t)cmd_count)
	{
		k = 0;
		while (j + k < (size_t)ac && ft_strncmp(av[j + k], "|\0", 2))
			++k;
		ret[i] = ft_splitlcpy(av + j, k);
		if (!ret[i])
			return (free_cmdargs(ret), NULL);
		j += k + 1;
		++i;
	}
	return (ret);
}

static void	free_cmdargs(char ***cmdargs)
{
	size_t	i;
	size_t	j;

	if (!cmdargs)
		return ;
	i = 0;
	while (cmdargs[i])
	{
		j = 0;
		while (cmdargs[i][j])
		{
			free(cmdargs[i][j]);
			++j;
		}
		free(cmdargs[i]);
		++i;
	}
	free(cmdargs);
}
