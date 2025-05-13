/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_reddir_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:58:18 by abronner          #+#    #+#             */
/*   Updated: 2025/05/13 11:59:22 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	red_open_file(char *filename, int flags, int mode);

static int	red_cut_cont(t_token *tok, size_t i);

int	red_open_file(char *filename, int flags, int mode)
{
	int		fd;

	fd = open(filename, flags, mode);
	if (!fd)
		errormsg(filename, strerror(errno));
	return (fd);
}

int	red_cut_cont(t_token *tok, size_t i)
{
	size_t	j;
	void	*new_cont;

	new_cont = malloc((tok->size - 1) * sizeof(void *));
	if (!new_cont)
		return (1);
	j = 0;
	while (j < i)
	{
		new_cont[j] = tok->cont[j];
		++j;
	}
	while (j < tok_size)
	{
		new_cont = tok->cont[j + 1];
		++j;
	}
	free(tok->cont[i]);
	free(tok->cont);
	tok->cont = new_cont;
	--tok->size;
	return (0);
}
