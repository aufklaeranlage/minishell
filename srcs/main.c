/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:21:01 by abronner          #+#    #+#             */
/*   Updated: 2025/04/02 14:13:26 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

int	main(int ac, char **av)
{
	int	*pids;
	int	pipeid;
	int	pipefd[2];
	int	children;

	if (ac != 2)
		return (1);
	children = ft_atoi(av[1]);
	pipeid = pipe_chain(children, pipefd, &pids);
	if (pipeid > 1)
		close(pipefd[1]);
	if (pipeid && pipeid < children)
		close(pipefd[0]);
	free(pids);
	return (0);
}
