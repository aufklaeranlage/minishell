/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@students.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:43:55 by abronner          #+#    #+#             */
/*   Updated: 2025/04/02 12:30:19 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_conv.h"

static size_t		ft_skippre(const char *nptr, long int *sign, int *base);

static int			ft_ofcheck(long int *val, long int dig, long int sign,
						int base);

static long int		ft_basechr(const char *s, int c, size_t n, size_t *offset);

long int	ft_strtol(const char *nptr, int base)
{
	long int	val;
	long int	sign;
	long int	dig;
	size_t		i;

	if (base < 0 || base == 1 || base > 36 || !nptr)
		return (0);
	i = ft_skippre(nptr, &sign, &base);
	val = 0;
	while (ft_basechr(BASE, ft_tolower(nptr[i]), base, (size_t *)&dig))
	{
		if (ft_ofcheck(&val, dig, sign, base))
			break ;
		val *= base;
		val += dig;
		++i;
	}
	val *= sign;
	return (val);
}

static size_t	ft_skippre(const char *nptr, long int *sign, int *base)
{
	size_t	i;

	i = 0;
	while (ft_isspace(nptr[i]))
		++i;
	*sign = 1;
	if (nptr[i] == '+' || nptr[i] == '-')
		*sign = (nptr[i] == '+') * 1 - (nptr[i] == '-');
	if (nptr[i] == '+' || nptr[i] == '-')
		++i;
	if (*base == 16 && ft_strncmp(nptr + i, "0x", 2))
		i += 2;
	else if (*base == 0 && nptr[i] == '0')
		*base = 8;
	else if (*base == 0)
		*base = 10;
	return (i);
}

static int	ft_ofcheck(long int *val, long int dig, long int sign, int base)
{
	if (sign == 1 && (LONG_MAX - dig) / base < *val)
	{
		*val = LONG_MAX;
		return (1);
	}
	else if (sign == -1 && -((LONG_MIN + dig) / base) < *val)
	{
		*val = LONG_MIN;
		return (1);
	}
	return (0);
}

static long int	ft_basechr(const char *s, int c, size_t n, size_t *offset)
{
	size_t	i;

	i = 0;
	while (s[i] && i < n)
	{
		if (s[i] == c)
			return (*offset = i, 1);
		++i;
	}
	*offset = -1;
	return (0);
}
