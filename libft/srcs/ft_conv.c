/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@students.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:41:06 by abronner          #+#    #+#             */
/*   Updated: 2025/04/02 12:29:30 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_conv.h"

int	ft_atoi(const char *nptr)
{
	long int	out;

	out = ft_strtol(nptr, 10);
	if (out > INT_MAX)
		out = INT_MAX;
	else if (out < INT_MIN)
		out = INT_MIN;
	return ((int)out);
}

char	*ft_itoa(int val)
{
	return (ft_ltostr(val, 10));
}
