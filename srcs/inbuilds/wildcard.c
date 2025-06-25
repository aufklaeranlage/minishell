/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:55:34 by akuzmin           #+#    #+#             */
/*   Updated: 2025/06/25 16:43:45 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inbuilds.h"
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h" // твоя библиотека

static char	*matches_to_string(t_wrap *matches);

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

int	match_tokens(char *content, char **tokens, int check_first)
{
	size_t	pos;
	size_t	i;
	char	*found;

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

	while (tokens[i])
	{
		found = ft_strnstr(content + pos, tokens[i], ft_strlen(content + pos));
		if (!found)
			return (0);
		pos = found - content + ft_strlen(tokens[i]);
		i++;
	}
	
	// последний токен — если непустой, должен быть в конце
	if (i > 1 && tokens[i - 1][0] != '\0')
	{
		size_t len = ft_strlen(tokens[i - 1]);
		size_t content_len = ft_strlen(content);
		if (content_len < len || ft_strncmp(content + content_len - len, tokens[i - 1], len))
			return (0);
	}
	return (1);
}

char *expand_wildcard(char *str)
{
	DIR				*dir;
	struct dirent	*entry;
	t_wrap			*matches;
	char			*result;
	char			**tokens;

	if (!str || !is_wildcard(str))
		return (ft_strdup(str));

	tokens = ft_split(str, '*');
	if (!tokens)
		return (NULL);

	matches = ft_calloc(1, sizeof(t_wrap));
	if (!matches)
		return (ft_freesplit(tokens), NULL);

	dir = opendir(".");
	if (!dir)
	{
		ft_freesplit(tokens);
		// free(matches);
		return (ft_strdup(str));
	}
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] == '.' && str[0] != '.')
			continue ;
		if (match_tokens(entry->d_name, tokens, str[0] != '*'))
			ft_wrapadd_back(matches, ft_lstnew(ft_strdup(entry->d_name)));
	}
	closedir(dir);
	ft_freesplit(tokens);
	result = matches_to_string(matches);
	ft_wrapclear(matches, free);
	// free(matches);
	if (!result || result[0] == '\0')
		return (NULL);
	return (result);
}

static char	*matches_to_string(t_wrap *matches)
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
