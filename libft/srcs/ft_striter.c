/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@students.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:43:38 by abronner          #+#    #+#             */
/*   Updated: 2025/04/02 12:27:14 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*out;
	size_t	slen;
	size_t	i;

	if (!s || !f)
		return (NULL);
	slen = ft_strlen(s) + 1;
	out = malloc(slen-- * sizeof(*out));
	if (!out)
		return (NULL);
	out[slen] = 0;
	i = 0;
	while (s[i])
	{
		out[i] = f(i, s[i]);
		++i;
	}
	return (out);
}

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, s + i);
		++i;
	}
}
