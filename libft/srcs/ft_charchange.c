/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charchange.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@students.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:41:00 by abronner          #+#    #+#             */
/*   Updated: 2025/04/02 12:48:18 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_ctype.h"

int	ft_toupper(int c)
{
	if (ft_islower(c))
		return (ft_toascii(c) - 32);
	return (c);
}

int	ft_tolower(int c)
{
	if (ft_isupper(c))
		return (ft_toascii(c) + 32);
	return (c);
}
