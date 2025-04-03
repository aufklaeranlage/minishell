/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cmdargs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:13:03 by abronner          #+#    #+#             */
/*   Updated: 2025/04/03 14:26:01 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

int	pipe_countcmds(int ac, char **av)
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

char	***pipe_setcmdargs(int ac, char **av, int cmd_count)
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

void	free_cmdargs(char ***cmdargs)
{
	size_t	i;

	if (!cmdargs)
		return ;
	i = 0;
	while (cmdargs[i])
	{
		ft_freesplit(cmdargs[i]);
		++i;
	}
	free(cmdargs);
}
