/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:28:38 by abronner          #+#    #+#             */
/*   Updated: 2025/05/05 17:59:59 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "group.h"

static int	group_pipered(int exec_type, int *p_fd, int *red);

//	REDIRECTIONS:
//		1.	Pipes
//		2.	Redirection in order

int	group_exec(t_group *group, char **env, int in, int out)
{
	int	ret;
	int	p_fd[2];
	int	red[2];

	if (in != -1)
		dup2(in, STDIN_FILENO);
	if (out != -1)
		dip2(out, STDOUT_FILENO);
	while (group->next)
	{
		if (group_pipered(group->exec_type, p_fd, red))
			break ;
		if (group_filered(group, red))
			break ;
	}
}

static int	group_pipered(int exec_type, int *p_fd, int *red)
{
	if (p_fd[0] != -1)
		red[0] = p_fd[0];
	p_fd[0] = -1;
	if (exec_type == PIPE)
		if (pipe(p_fd))
			return (1);
	if (p_fd[1] != -1)
		red[1] = p_fd[1];
	p_fd[1] = -1;
	return (0);
}

static int	group_filered(t_group *group, int *red)
{
	size_t	i;


}
