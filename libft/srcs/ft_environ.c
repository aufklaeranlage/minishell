/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_environ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 09:30:20 by abronner          #+#    #+#             */
/*   Updated: 2025/04/02 12:52:07 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_env.h"

char	*ft_getenv(const char *name)
{
	char	*tmp;
	size_t	len;
	size_t	i;

	len = ft_strlen(name);
	i = 0;
	while (environ[i])
	{
		tmp = ft_strnstr(environ[i], name, len);
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

	tmp = ft_strchr(paths, '=');
	if (!tmp)
		return (NULL);
	ret = ft_split(tmp, ':');
	return (ret);
}
