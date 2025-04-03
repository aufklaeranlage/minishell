/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:18:36 by abronner          #+#    #+#             */
/*   Updated: 2025/04/03 15:25:51 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

void	pipe_errormsg(char *errorstr, char *filename, int w_pid)
{
	if (!filename || !errorstr)
		return ;
	waitpid(w_pid, NULL, 0);
	write(2, SHELL_NAME, SHELL_NAME_LEN);
	if (errorstr)
	{
		write(2, ": ", 2);
		write(2, errorstr, ft_strlen(errorstr));
	}
	if (filename)
	{
		write(2, ": ", 2);
		write(2, filename, ft_strlen(filename));
	}
	write(2, "\n", 1);
}

void	pipe_cleanup(int pipeid, t_pipeutils *p_utils)
{
	if (p_utils->paths)
		ft_freesplit(p_utils->paths);
	if (p_utils->cmdargs)
		free_cmdargs(p_utils->cmdargs);
	if (pipeid > 1)
		close(p_utils->p_fd[0]);
	if ((size_t)pipeid < p_utils->cmd_count)
		close(p_utils->p_fd[1]);
	free(p_utils->pids);
	if (p_utils->red_fd != -1)
		close(p_utils->red_fd);
}
