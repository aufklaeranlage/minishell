/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctype_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@students.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:41:21 by abronner          #+#    #+#             */
/*   Updated: 2025/04/02 12:42:49 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_ctype.h"

int	ft_iscntrl(int c)
{
	c = ft_toascii(c);
	if ((c >= 0x0 && c <= 0x1f) || c == 0x7f)
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	c = ft_toascii(c);
	if (c >= 0x30 && c <= 0x39)
		return (c);
	return (0);
}

int	ft_isgraph(int c)
{
	c = ft_toascii(c);
	if (c > 0x20 && c < 0x7f)
		return (c);
	return (0);
}

int	ft_islower(int c)
{
	c = ft_toascii(c);
	if (c >= 0x61 && c <= 0x7a)
		return (c);
	return (0);
}

int	ft_isprint(int c)
{
	c = ft_toascii(c);
	if (c >= 0x20 && c < 0x7f)
		return (c);
	return (0);
}
