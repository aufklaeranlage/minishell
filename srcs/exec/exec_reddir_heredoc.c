/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_reddir_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:28:07 by abronner          #+#    #+#             */
/*   Updated: 2025/05/21 11:33:06 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	open_heredoc(char *filename)
{
	int		fd;

	fd = open(filename, O_RDONLY, 0);
	unlink(filename);
	return (fd);
}
