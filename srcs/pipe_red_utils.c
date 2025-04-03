/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_red_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:16:18 by abronner          #+#    #+#             */
/*   Updated: 2025/04/03 14:48:12 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

int	pipe_red_cutcmd(char ***cmdargs, size_t argindex, size_t len)
{
	char	**cut_cmd;

	cut_cmd = ft_cutsplit((const char **)*cmdargs, argindex, len);
	if (!cut_cmd)
		return (1);
	ft_freesplit(*cmdargs);
	*cmdargs = cut_cmd;
	return (0);
}
