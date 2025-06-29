/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quatation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:22:19 by akuzmin           #+#    #+#             */
/*   Updated: 2025/06/30 00:06:37 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenisation.h"
#include "expander.h"

static int	ft_splitappend(char ***dst, char *src)
{
	size_t	dcount;
	char	**app;
	size_t	scount;
	char	**ret;

	if (!dst || !src)
		return (1);
	app = ft_split(src, ' ');
	dcount = ft_splitcount((const char **)*dst);
	scount = ft_splitcount((const char **)app);
	if (!dcount && !scount)
		return (0);
	ret = malloc((dcount + scount + 1) * sizeof(*ret));
	if (!ret)
		return (1);
	ret[dcount + scount] = NULL;
	while (scount--)
		ret[dcount + scount] = app[scount];
	while (dcount--)
		ret[dcount] = (*dst)[dcount];
	free(*dst);
	free(app);
	*dst = ret;
	return (1);
}

static int	replace_tokens(t_tokens *tok, char **split)
{
	size_t	size;
	int		*types;
	size_t	i;

	size = ft_splitcount((const char **)split);
	types = malloc(size * sizeof(*types));
	if (!types)
		return (1);
	i = 0;
	while (i < size)
	{
		types[i] = set_type(split[i]);
		++i;
	}
	ft_freesplit(tok->content);
	tok->content = split;
	free(tok->type);
	tok->type = types;
	tok->size = size;
	return (0);
}

/**
 * @brief Removes quotes and expands environment variables from a given string.
 * Handles both single ('') and double ("") quotes. 
 * Single quotes prevent expansion.
 * Double-quoted and unquoted segments may be expanded via @ref expand_path.
 * @see expand_path()
 * @param str Input string to be processed.
 * @param env Environment variables for expansion.
 * @return Newly allocated string with quotes removed and variables expanded.
 */
int	handle_quotes(t_tokens *tok, t_env *env)
{
	char	**newsplits;
	char	*expand;
	char	*str;
	size_t	i;

	i = 0;
	newsplits = ft_calloc(1, sizeof(*newsplits));
	while (i < tok->size)
	{
		str = tok->content[i];
		if (is_wildcard(str))
			expand = expand_wildcard(str, env);
		else
			expand = get_expandet(str, env);
		if (!ft_splitappend(&newsplits, expand))
			return (1);
		if (expand)
			free(expand);
		i++;
	}
	if (replace_tokens(tok, newsplits))
		return (ft_freesplit(newsplits), 1);
	return (0);
}
