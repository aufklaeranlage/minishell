/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:55:34 by akuzmin           #+#    #+#             */
/*   Updated: 2025/06/25 18:09:32 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inbuilds.h"
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

char		*matches_to_string(t_wrap *matches);

int			match_tokens(char *content, char **tokens, int check_first);

static char	*expand_wildcard_util(char *str, DIR *dir, t_wrap *mt, char **t)
{
	char			*result;
	struct dirent	*entry;

	dir = opendir(".");
	while (1)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		if (entry->d_name[0] == '.' && str[0] != '.')
			continue ;
		if (match_tokens(entry->d_name, t, str[0] != '*'))
			ft_wrapadd_back(mt, ft_lstnew(ft_strdup(entry->d_name)));
	}
	closedir(dir);
	ft_freesplit(t);
	result = matches_to_string(mt);
	ft_wrapclear(mt, free);
	if (!result || result[0] == '\0')
		return (NULL);
	return (result);
}

char	*expand_wildcard(char *str)
{
	DIR				*dir;
	t_wrap			*matches;
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
		return (ft_freesplit(tokens), ft_strdup(str));
	return (expand_wildcard_util(str, dir, matches, tokens));
}
