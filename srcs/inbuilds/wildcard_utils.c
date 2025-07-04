/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:55:34 by akuzmin           #+#    #+#             */
/*   Updated: 2025/07/04 16:03:03 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inbuilds.h"
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

int	is_wildcard(char *str)
{
	size_t	i;
	char	quote;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				i++;
			if (str[i])
				i++;
		}
		else if (str[i] == '*')
			return (1);
		else
			i++;
	}
	return (0);
}

int	match_tokens_util(char *cnt, char **tokens, size_t	i, size_t pos)
{
	char	*found;
	size_t	len;
	size_t	cnt_len;

	while (tokens[i])
	{
		found = ft_strnstr(cnt + pos, tokens[i], ft_strlen(cnt + pos));
		if (!found)
			return (0);
		pos = found - cnt + ft_strlen(tokens[i]);
		i++;
	}
	if (i > 1 && tokens[i - 1][0] != '\0')
	{
		len = ft_strlen(tokens[i - 1]);
		cnt_len = ft_strlen(cnt);
		if (cnt_len < len \
			|| ft_strncmp(cnt + cnt_len - len, tokens[i - 1], len))
			return (0);
	}
	return (1);
}

int	match_tokens(char *content, char **tokens, int check_first)
{
	size_t	pos;
	size_t	i;

	if (!content || !tokens)
		return (0);
	if (!*tokens)
		return (1);
	pos = 0;
	i = 0;
	if (check_first)
	{
		if (ft_strncmp(content, tokens[0], ft_strlen(tokens[0])) != 0)
			return (0);
		pos = ft_strlen(tokens[0]);
		++i;
	}
	return (match_tokens_util(content, tokens, i, pos));
}

char	*matches_to_string(t_wrap *matches)
{
	t_list	*current;
	char	*result;

	if (!matches || !matches->head)
		return (NULL);
	current = matches->head;
	result = ft_strdup((char *)current->content);
	if (!result)
		return (NULL);
	current = current->next;
	while (current)
	{
		result = strjoin_and_free(result, " ");
		result = strjoin_and_free(result, (char *)current->content);
		current = current->next;
	}
	return (result);
}
