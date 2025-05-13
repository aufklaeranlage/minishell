/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_reddir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:31:15 by abronner          #+#    #+#             */
/*   Updated: 2025/05/13 11:58:45 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	red_out(t_token *tok, int fd[2], size_t i);

static void	red_in(t_token *tok, int fd[2], size_t i);

int	exec_reddir(t_token *tok)
{
	size_t	i;
	int		fd[2];

	bzero(fd, 2 * sizeof(fd));
	i = 0;
	while (i < tok->size)
	{
		if (tok->type >= RED_LOWEST && tok->type <= RED_HIGHEST)
		{
			if ((tok->type == RED_IN || tok->type == HERE_DOC))
				red_in(tok, fd, i);
			if ((tok->type == RED_OUT || tok->type == APP_OUT))
				red_out(tok, fd, i);
			if (red_cut_cont(tok, i))
				return (-1);
		}
		else
			++i;
	}
}

static void	red_in(t_token *tok, int fd[2], size_t i)
{
	if (fd[0])
		close(fd[0]);
	if (tok->type[i] == RED_IN)
		fd[0] = red_open_file((char *)tok->cont[i], O_RDONLY, NULL);
	else if (tok->type == HERE_DOC)
		fd[0] = open_here((char *)tok->cont[i]);
}

static void	red_out(t_token *tok, int fd[2], size_t i)
{
	if (fd[1])
		close(fd[1]);
	if (tok->type[i] == RED_OUT)
		fd[1] = red_open_file((char *)tok->cont[i],
				O_WRONLY | O_CREAT | O_TRUNC, NULL);
	else if (tok->type[i] == ADD_OUT)
		fd[1] = red_open_file((char *)tok->cont[i],
				O_WRONLY | O_CREAT | O_APPEND, NULL);
}
