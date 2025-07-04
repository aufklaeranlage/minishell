/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quatation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:22:19 by akuzmin           #+#    #+#             */
/*   Updated: 2025/07/04 16:21:37 by abronner         ###   ########.fr       */
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

	dcount = 0;
	if (dst)
		dcount = ft_splitcount((const char **)*dst);
	app = ft_split(src, ' ');
	scount = ft_splitcount((const char **)app);
	ret = malloc((dcount + scount + 1) * sizeof(*ret));
	if (!ret)
		return (free(src), 1);
	ret[dcount + scount] = NULL;
	while (scount--)
		ret[dcount + scount] = app[scount];
	while (dcount--)
		ret[dcount] = (*dst)[dcount];
	free(*dst);
	free(app);
	free(src);
	*dst = ret;
	return (1);
}

static int	ft_strappend(char ***dst, char *src)
{
	size_t	dcount;
	char	**ret;

	dcount = 0;
	if (dst)
		dcount = ft_splitcount((const char **)*dst);
	ret = malloc((dcount + 2) * sizeof(*ret));
	if (!ret)
		return (free(src), 1);
	ret[dcount + 1] = NULL;
	ret[dcount] = src;
	while (dcount--)
		ret[dcount] = (*dst)[dcount];
	free(*dst);
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
	char	*str;
	size_t	i;

	i = 0;
	newsplits = NULL;
	while (i < tok->size)
	{
		str = tok->content[i];
		if (is_wildcard(str))
			ft_splitappend(&newsplits, expand_wildcard(str, env));
		else
			ft_strappend(&newsplits, get_expandet(str, env));
		i++;
	}
	if (replace_tokens(tok, newsplits))
		return (ft_freesplit(newsplits), 1);
	return (0);
}

int	redirection_quotes(char **str, t_env *env)
{
	char	**newsplits;
	size_t	i;

	newsplits = NULL;
	if (is_wildcard(*str))
		ft_splitappend(&newsplits, expand_wildcard(*str, env));
	else
		ft_strappend(&newsplits, get_expandet(*str, env));
	if (!newsplits)
		return (0);
	i = 0;
	while (newsplits[i])
		++i;
	if (i > 1)
		return (errormsg(SHNAME, *str, "ambiguous redirect", NULL),
		ft_freesplit(newsplits), 1);
	free(*str);
	*str = newsplits[0];
	free(newsplits);
	return (0);
}
