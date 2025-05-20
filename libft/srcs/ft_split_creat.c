/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_creat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:30:56 by abronner          #+#    #+#             */
/*   Updated: 2025/05/19 11:57:13 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"

char	**ft_splitlcpy(char **split, size_t len)
{
	size_t	i;
	char	**ret;

	ret = malloc((len + 1) * sizeof(*ret));
	if (!ret)
		return (NULL);
	ret[len] = NULL;
	i = 0;
	while (i < len)
	{
		ret[i] = ft_strdup(split[i]);
		if (!ret[i])
			return (ft_freesplit(ret), NULL);
		++i;
	}
	return (ret);
}

char	**ft_cutsplit(const char **split, size_t offset, size_t cut_len)
{
	char	**ret;
	size_t	split_len;
	size_t	i;

	split_len = ft_splitcount(split);
	if (!split_len || split_len < offset || split_len < offset + cut_len)
		return (NULL);
	ret = malloc((split_len - cut_len + 1) * sizeof(*ret));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < offset)
	{
		ret[i] = ft_strdup(split[i]);
		if (!ret[i++])
			return (ft_freesplit(ret), NULL);
	}
	while (i < split_len - cut_len)
	{
		ret[i] = ft_strdup(split[i + cut_len]);
		if (!ret[i++])
			return (ft_freesplit(ret), NULL);
	}
	return (ret);
}
