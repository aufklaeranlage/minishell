/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@students.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:43:29 by abronner          #+#    #+#             */
/*   Updated: 2025/04/02 15:50:57 by abronner         ###   ########.fr       */
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

void	ft_freesplit(char **split)
{
	size_t	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

char	**ft_splitlcpy(char **splits, size_t	len)
{
	char	**ret;
	size_t	i;

	ret = malloc((len + 1) * sizeof(*ret));
	if (!ret || !splits)
		return (NULL);
	ret[len] = NULL;
	i = 0;
	while (i < len)
	{
		if (!splits[i])
		{
			ret[i] = NULL;
			return (ft_freesplit(ret), NULL);
		}
		ret[i] = ft_strdup(splits[i]);
		if (!ret[i])
			return (ft_freesplit(ret), NULL);
		++i;
	}
	return (ret);
}
