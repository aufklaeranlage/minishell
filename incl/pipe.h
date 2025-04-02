/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:23:00 by abronner          #+#    #+#             */
/*   Updated: 2025/04/02 14:55:07 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

# include <stdlib.h>
# include <unistd.h>

# include "libft.h"

//	DEFINES

# define STDIN_FILENO 0
# define STDOUT_FILENO 1
# define STDERR_FILENO 2

//	FUNCTIONS

int		pipe_chain(int chainlinks, int p_fd[2], pid_t **pids);

void	pipe_connector(int pipefd[2], int pipeid, int max_pipeid);

#endif
