/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltostr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@students.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:42:50 by abronner          #+#    #+#             */
/*   Updated: 2025/04/02 12:30:05 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_conv.h"

static size_t	ft_ltostr_getsize(long int val, int base);

static void		ft_ltostr_setpre(char *out, long int val, size_t size);

char	*ft_ltostr(long int val, int base)
{
	char	*out;
	char	*basestr;
	size_t	size;
	int		dig;

	basestr = ft_substr(BASE, 0, base);
	if (!basestr)
		return (NULL);
	size = ft_ltostr_getsize(val, base) + 1;
	out = malloc(size-- * sizeof(*out));
	if (!out)
		return (free(basestr), NULL);
	ft_ltostr_setpre(out, val, size--);
	while (val)
	{
		dig = val % base;
		val /= base;
		if (dig < 0)
		{
			dig *= -1;
			val *= -1;
		}
		out[size--] = basestr[dig];
	}
	return (free(basestr), out);
}

static size_t	ft_ltostr_getsize(long int val, int base)
{
	size_t	size;

	size = 0;
	if (val == 0)
		++size;
	else if (val < 0)
		++size;
	while (val)
	{
		val /= base;
		++size;
	}
	return (size);
}

static void	ft_ltostr_setpre(char *out, long int val, size_t size)
{
	if (val < 0)
		out[0] = '-';
	if (val == 0)
		out[0] = '0';
	out[size] = 0;
}
