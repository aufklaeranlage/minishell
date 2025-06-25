/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quatation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:22:19 by akuzmin           #+#    #+#             */
/*   Updated: 2025/06/25 18:46:59 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenisation.h"
#include "expander.h"

/**
 * @brief Joins two strings and frees the first one.
 *
 * @param s1 First string, will be freed.
 * @param s2 Second string.
 * @return Newly allocated string containing the result of s1 + s2.
 */
char	*strjoin_and_free(char *s1, char *s2)
{
	char	*res;

	if (!s1)
		res = ft_strdup(s2);
	else if (!s2)
		res = ft_strdup(s1);
	else
		res = ft_strjoin(s1, s2);
	free(s1);
	return (res);
}

static char	*handle_quoted_segment(char **out, char *p, t_env *env)
{
	char	*tmp;
	char	*exp;
	char	quote;

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
	if (!ft_strchr(p, quote))
		return (p + ft_strlen(p));
	return (ft_strchr(p, quote) + 1);
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
	free(tmp);
	*out = strjoin_and_free(*out, exp);
	free(exp);
	return (q);
}

static int	ft_splitappend(char ***dst, char *src)
{
	size_t	dcount;
	char	**app;
	size_t	scount;
	char	**ret;

	if (!dst)
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
		expand = ft_strdup("");
		while (*str)
		{
			if (*str == '\'' || *str == '"')
				str = handle_quoted_segment(&expand, str, env);
			else
				str = handle_unquoted_segment(&expand, str, env);
		}
		if (is_wildcard(str))
			expand = expand_wildcard(expand);
		if (!ft_splitappend(&newsplits, expand))
			return (free(expand), 1);
		free(expand);
		++i;
	}
	if (replace_tokens(tok, newsplits))
		return (ft_freesplit(newsplits), 1);
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
