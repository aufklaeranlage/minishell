/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsearch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@students.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:43:46 by abronner          #+#    #+#             */
/*   Updated: 2025/04/02 12:47:46 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		++len;
	return (len);
}

/*	Returns the first occurence of char c in str s.
 *	Requires a properly terminated c string.
*/

char	*ft_strchr(const char *s, int c)
{
	c = ft_toascii(c);
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		++s;
	}
	if (*s == c)
		return ((char *)s);
	return (NULL);
}

/*	Returns the last occurence of char c in str s.
 *	Requires a properly terminated c string.
*/

char	*ft_strrchr(const char *s, int c)
{
	char	*out;

	out = NULL;
	c = ft_toascii(c);
	while (*s)
	{
		if (*s == c)
			out = (char *)s;
		++s;
	}
	if (*s == c)
		out = (char *)s;
	return (out);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		diff;

	i = 0;
	while (i < n)
	{
		diff = s1[i] - s2[i];
		if (diff)
			return (diff);
		++i;
	}
	return (0);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	slen;

	slen = ft_strlen(little);
	if (!slen)
		return ((char *)big);
	i = 0;
	while (big[i] && i + slen <= len)
	{
		if (!ft_strncmp(big + i, little, slen))
			return ((char *)(big + i));
		++i;
	}
	return (NULL);
}
