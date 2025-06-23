/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups_delimiter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 23:03:56 by akuzmin           #+#    #+#             */
/*   Updated: 2025/06/23 23:34:40 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/tokenisation.h"

int	set_type(char *tmp, char **env)
{
	char	*exec;

	if (specifier_one(tmp))
		return (specifier_one(tmp));
	if (specifier_two(tmp))
		return (specifier_two(tmp));
	if (cmd_specifier(tmp))
		return (cmd_specifier(tmp));
	exec = minishell_getexec(tmp, env);
	if (exec)
		return (free(exec), STD_CMD);
	free(exec);
	if (is_falg(tmp))
		return (FLAG);
	else
		return (TEXT);
}

size_t	delimiter(int *d_type, t_tokens *list, size_t i)
{
	while (i < list->size)
	{
		if (list->type[i] == PIPE || list->type[i] == OR \
			|| list->type[i] == AND || list->type[i] == SMCLN)
		{
			*d_type = list->type[i];
			return (i);
		}
		i++;
	}
	return (0);
}
