/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:29:52 by abronner          #+#    #+#             */
/*   Updated: 2025/07/04 12:12:09 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	**exec_cutassign(char **src, size_t size, size_t offset);

int	exec_assign(t_tokens *tok, t_env *env)
{
	char	**tmp;
	size_t	i;

	i = 0;
	while (i < tok->size && ft_strchr(tok->content[i], '=' ))
	{
		env_ins(tok->content[i], ENVSET, env);
		++i;
	}
	while (i < tok->size && tok->content[i][0] == '\0')
		++i;
	if (i == 0)
		return (0);
	tmp = exec_cutassign(tok->content, tok->size, i);
	if (!tmp)
		return (1);
	free(tok->content);
	tok->content = tmp;
	tok->size -= i;
	return (0);
}

static char	**exec_cutassign(char **src, size_t size, size_t offset)
{
	char	**ret;
	size_t	i;

	ret = malloc((size - offset + 1) * sizeof(*ret));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < size - offset)
	{
		ret[i] = src[offset + i];
		++i;
	}
	ret[i] = NULL;
	return (ret);
}

int	childreturn(int wstatus)
{
	if (wstatus == 0)
		return (0);
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	if (WIFSIGNALED(wstatus))
		return (WTERMSIG(wstatus));
	return (-1);
}
