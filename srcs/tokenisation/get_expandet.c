/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_expandet.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:22:19 by akuzmin           #+#    #+#             */
/*   Updated: 2025/07/01 08:11:29 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenisation.h"
#include "expander.h"

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

/**
 * @brief Get the expandet string (str)
 * 
 * @param str input string with quots, ist can be mexied or not
 * @param env enviroment
 * @return char* (string) after 'opening' quots.
 */
char	*get_expandet(char *str, t_env *env)
{
	char	*expand;

	expand = ft_strdup("");
	while (*str)
	{
		if (*str == '\'' || *str == '"')
			str = handle_quoted_segment(&expand, str, env);
		else
			str = handle_unquoted_segment(&expand, str, env);
	}
	return (expand);
}
