/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@students.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:43:29 by abronner          #+#    #+#             */
/*   Updated: 2025/05/21 15:43:19 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"

static size_t	ft_countsplits(const char *s, char delimiter);

char	**ft_split(const char *s, char delimiter)
{
	char	**out;
	size_t	splits;
	size_t	i;
	char	*tmp;

	splits = ft_countsplits(s, delimiter) + 1;
	out = malloc(splits-- * sizeof(*out));
	if (!out)
		return (NULL);
	i = 0;
	while (i < splits)
	{
		while (*s == delimiter)
			++s;
		tmp = ft_strchr(s, delimiter);
		if (!tmp)
			tmp = ft_strchr(s, '\0');
		out[i] = ft_substr(s, 0, (size_t)(tmp - s));
		if (!out[i])
			return (ft_freesplit(out), NULL);
		s = tmp;
		++i;
	}
	out[i] = NULL;
	return (out);
}

/*	Has inbuild safety for split since it will return 0 splits on an emptpy
 *	string
*/

static size_t	ft_countsplits(const char *s, char delimiter)
{
	size_t	splits;

	splits = 0;
	while (*s)
	{
		while (*s == delimiter)
			++s;
		if (*s)
			++splits;
		while (*s && *s != delimiter)
			++s;
	}
	return (splits);
}

size_t	ft_splitcount(const char **split)
{
	size_t	ret;

	if (!split)
		return (0);
	ret = 0;
	while (split[ret])
		++ret;
	return (ret);
}

void	ft_freesplit(char **split)
{
	size_t	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		++i;
	}
	free(split);
}
