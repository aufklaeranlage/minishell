/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:23:00 by abronner          #+#    #+#             */
/*   Updated: 2025/04/03 16:51:53 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>

# include "libft.h"

//	DEFINES

# define STDIN_FILENO 0
# define STDOUT_FILENO 1
# define STDERR_FILENO 2

# define SHELL_NAME "shelltered"
# define HERE_DOC_MSG "here_doc > "

# define RED_IN 0b10
# define RED_OUT 0b100

//	TYPEDEFS

typedef struct s_pipeutils
{
	char		**paths;
	char		***cmdargs;
	size_t		cmd_count;
	int			p_fd[2];
	int			*pids;
	int			red_fd;
	short		red_type;
}	t_pipeutils;

//	PIPE

int		pipe_chain(int chainlinks, int p_fd[2], pid_t **pids);

void	pipe_connector(int p_fd[2], int pipeid, int max_pipeid, int red_flag);

void	pipe_closer(int p_fd[2], int pipeid, int max_pipeid);

//	PIPE CMDARGS

int		pipe_countcmds(int ac, char **av);

char	***pipe_setcmdargs(int ac, char **av, int cmd_count);

void	free_cmdargs(char ***cmdargs);

//	PIPE REDIRECTIONS

int		pipe_red_check(int pipeid, t_pipeutils *eutils);

//	PIPE REDIRECTIONS UTILS

int		pipe_red_cutcmd(char ***cmdargs, size_t argindex, size_t len);

//	PIPE ERROR

void	pipe_errormsg(char *errorstr, char *filename, int w_pid);

void	pipe_cleanup(int pipeid, t_pipeutils *p_utils);

#endif
