/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctype_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@students.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:42:23 by abronner          #+#    #+#             */
/*   Updated: 2025/04/02 12:42:59 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_ctype.h"

int	ft_ispunct(int c)
{
	c = ft_toascii(c);
	if (ft_isgraph(c) && !ft_isalnum(c))
		return (c);
	return (0);
}

//	space, form-feed, newline, carriage return, horizontal tab, vertical tab

int	ft_isspace(int c)
{
	c = ft_toascii(c);
	if (c == 0x20 || (c >= 0x9 && c <= 0xd))
		return (c);
	return (0);
}

int	ft_isupper(int c)
{
	c = ft_toascii(c);
	if (c >= 0x41 && c <= 0x5a)
		return (c);
	return (0);
}

int	ft_isxdigit(int c)
{
	c = ft_toascii(c);
	if (ft_isdigit(c) || (c >= 0x41 && c <= 0x46) || (c >= 0x61 && c <= 0x66))
		return (c);
	return (0);
}
