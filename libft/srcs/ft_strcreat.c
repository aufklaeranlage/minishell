/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcreat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@students.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:43:34 by abronner          #+#    #+#             */
/*   Updated: 2025/04/02 12:25:38 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"

char	*ft_strdup(const char *s)
{
	char	*out;
	size_t	slen;

	slen = ft_strlen(s) + 1;
	out = malloc(slen * sizeof(*out));
	if (!out)
		return (NULL);
	ft_strlcpy(out, s, slen);
	return (out);
}

/*	Appends s2 to the end of s1. Doesn't change the strings
 *	instead returns a pointer to a newly created string.
 *	Return NULL on mallloc fail.
*/

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*out;
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	out = malloc(len-- * sizeof(char));
	if (!out)
		return (NULL);
	len = 0;
	while (*s1)
	{
		out[len] = *s1;
		++s1;
		++len;
	}
	while (*s2)
	{
		out[len] = *s2;
		++s2;
		++len;
	}
	out[len] = '\0';
	return (out);
}

/*	Creates a substring out of the string s starting  at an offset of start till
 *	position end in the string.
 *	Will return NULL if start is bigger than the stringlength.
 *	Will return NULL if malloc fails.
 *	Will return a concatenated string if strign ends before end.
*/

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*out;
	size_t	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (slen < start)
		slen = 0;
	else
		slen -= start;
	if (len > slen)
		len = slen;
	++len;
	out = malloc(len * sizeof(char));
	if (!out)
		return (NULL);
	if (len > 1)
		ft_strlcpy(out, s + start, len);
	else
		out[0] = 0;
	return (out);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*out;
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		++start;
	end = ft_strlen(s1);
	while (end > start && ft_strrchr(set, s1[end]))
		--end;
	out = ft_substr(s1, start, end + 1 - start);
	return (out);
}
