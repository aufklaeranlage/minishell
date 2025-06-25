/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quatation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:22:19 by akuzmin           #+#    #+#             */
/*   Updated: 2025/06/25 15:51:19 by abronner         ###   ########.fr       */
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

	res = ft_strjoin(s1, s2);
	free(s1);
	return (res);
}

static char	*handle_quoted_segment(char **out, char *p, char **env)
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

static char	*handle_unquoted_segment(char **out, char *p, char **env)
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
char	*handle_quotes(char *str, char **env)
{
	char	*out;
	char	*p;

	if (!str)
		return (NULL);
	out = ft_calloc(1, 1);
	if (!out)
		return (NULL);
	p = str;
	while (*p)
	{
		if (*p == '\'' || *p == '"')
			p = handle_quoted_segment(&out, p, env);
		else
			p = handle_unquoted_segment(&out, p, env);
		if (is_wildcard(str))
			out = expand_wildcard(out);
	}
	free(str);
	return (out);
}

/**
 * @brief Updates the content of a token list by handling quotes and expansions.
 * Applies @ref handle_quotes to each element in the t_wrap list.
 * @see handle_quotes()
 * @param list Linked list of tokens to process.
 * @param env Environment variables for expansion.
 * @return 0 on success, 1 if input is NULL.
 */
int	update_values(t_wrap *list, char **env)
{
	t_list	*lst;
	size_t	i;

	if (!list || !list->head)
		return (1);
	lst = list->head;
	i = 0;
	while (i < list->size)
	{
		lst->content = (void *)handle_quotes(lst->content, env);
		lst = lst->next;
		i++;
	}
	return (0);
}
