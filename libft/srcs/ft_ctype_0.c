/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctype_0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@students.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:41:16 by abronner          #+#    #+#             */
/*   Updated: 2025/04/02 12:42:43 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_ctype.h"

int	ft_toascii(int c)
{
	return (c & 0177);
}

/*	~ is the bitwise complement operator that inverts the bits of the given
 *	number. Example: ~0001 = 1110.
 */

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 0x7f);
}

int	ft_isalnum(int c)
{
	c = ft_toascii(c);
	if (ft_isalpha(c) || ft_isdigit(c))
		return (c);
	return (0);
}

int	ft_isalpha(int c)
{
	c = ft_toascii(c);
	if (ft_isupper(c) || ft_islower(c))
		return (c);
	return (0);
}

int	ft_isblank(int c)
{
	c = ft_toascii(c);
	if (c == 0x20 || c == 0x9)
		return (1);
	return (0);
}
