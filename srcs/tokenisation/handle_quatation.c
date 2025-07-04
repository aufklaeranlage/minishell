/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quatation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:22:19 by akuzmin           #+#    #+#             */
/*   Updated: 2025/06/26 16:36:57 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenisation.h"
#include "expander.h"

static char	*handle_unquoted_segment(char **out, char *p, t_env *env);

static char	*handle_quoted_segment(char **out, char *p, t_env *env)
{
	char	*tmp;
	char	*exp;
	char	quote;
	char	*q;

	quote = *p++;
	if (ft_strchr(p, quote))
		tmp = ft_substr(p, 0, (size_t)(ft_strchr(p, quote) - p));
	else
		tmp = ft_substr(p, 0, ft_strlen(p));
	if (!tmp)
		return (NULL);
	if (quote == '\'')
		exp = tmp;
	else
	{
		exp = expand_path(tmp, env);
		free(tmp);
	}
	*out = strjoin_and_free(*out, exp);
	q = ft_strchr(p, quote);
	if (!q)
		return (p + ft_strlen(p));
	if (q[1] && (q[1] == '\'' || q[1] == '"'))
	 	return (handle_quoted_segment(out, q + 1, env));
	if (q[1] && !ft_isspace(q[1]))
	 	return (handle_unquoted_segment(out, q + 1, env));
	return (q + 1);
}

static char	*handle_unquoted_segment(char **out, char *p, t_env *env)
{
	char	*tmp;
	char	*exp;
	char	*q;

	q = p;
	while (*q && *q != '\'' && *q != '"')
		q++;
	tmp = ft_substr(p, 0, q - p);
	if (!tmp)
		return (NULL);
	exp = expand_path(tmp, env);
	if (is_wildcard(exp))
		exp = expand_wildcard(exp);
	free(tmp);
	*out = strjoin_and_free(*out, exp);
	free(exp);
	if (q[0] && (q[0] == '\'' || q[0] == '"'))
	 	return (handle_quoted_segment(out, q, env));
	return (q);
}

static int	ft_strappend(char ***dst, char *src)
{
	size_t	dcount;
	char	*str;
	char	**ret;

	if (!dst)
		return (1);
	dcount = ft_splitcount((const char **)*dst);
	ret = malloc((dcount + 2) * sizeof(*ret));
	str = ft_strdup(src);
	if (!ret || !str)
		return (free(str), free(ret), 1);
	ret[dcount + 1] = NULL;
	ret[dcount] = str;
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

static int handle_quotes_loop(t_tokens *tok, char ***newsplit, t_env *env)
{
	char	*expand;
	char	*str;
	size_t	i;

	i = 0;
	while (i < tok->size)
	{
		str = tok->content[i];
		expand = ft_strdup("");
		while (*str)
		{
			if (*str == '\'' || *str == '"')
				str = handle_quoted_segment(&expand, str, env);
			else
				str = handle_unquoted_segment(&expand, str, env);
			if (!ft_strappend(newsplit, expand))
				return (free(expand), 1);
		}
		free(expand);
		++i;
	}
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
	char	**newsplit;

	if (!tok || !tok->size)
		return (0);
	newsplit = ft_calloc(1, sizeof(*newsplit));
	if (handle_quotes_loop(tok, &newsplit, env))
		return (ft_freesplit(newsplit), 1);
	if (replace_tokens(tok, newsplit))
		return (ft_freesplit(newsplit), 1);
	return (0);
}

/**
 * @brief Updates the content of a token list by handling quotes and expansions.
 * Applies @ref handle_quotes to each element in the t_wrap list.
 * @see handle_quotes()
 * @param list Linked list of tokens to process.
 * @param env Environment variables for expansion.
 * @return 0 on success, 1 if input is NULL.
 */
// int	update_values(t_wrap *list, char **env)
// {
// 	t_list	*lst;
// 	size_t	i;
//
// 	if (!list || !list->head)
// 		return (1);
// 	lst = list->head;
// 	i = 0;
// 	while (i < list->size)
// 	{
// 		handle_quotes((t_tokens *)lst, env);
// 		lst = lst->next;
// 		i++;
// 	}
// 	return (0);
// }
