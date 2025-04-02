/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_environ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 09:30:20 by abronner          #+#    #+#             */
/*   Updated: 2025/04/02 14:44:27 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_env.h"

char	*ft_getenv(const char *name, const char **env)
{
	char	*tmp;
	size_t	len;
	size_t	i;

	if (!env || !name)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		tmp = ft_strnstr(env[i], name, len);
		if (tmp)
			break ;
		++i;
	}
	return (tmp);
}

char	**ft_splitpaths(const char *paths)
{
	char	**ret;
	char	*tmp;

	if (!paths)
		return (NULL);
	tmp = ft_strchr(paths, '=');
	if (!tmp)
		return (NULL);
	ret = ft_split(tmp, ':');
	return (ret);
}
