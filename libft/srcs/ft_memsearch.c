/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memsearch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@students.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:43:20 by abronner          #+#    #+#             */
/*   Updated: 2025/04/02 12:38:03 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mem.h"

void	*ft_memchr(const void *dest, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*(char *)(dest + i) == ft_toascii(c))
			return ((void *)(dest + i));
		++i;
	}
	return (NULL);
}

void	*ft_memrchr(const void *dest, int c, size_t n)
{
	size_t	i;

	if (n == 0)
		return (NULL);
	i = n - 1;
	while (i > 0)
	{
		if (*(char *)(dest + i) == ft_toascii(c))
			return ((void *)(dest + i));
		++i;
	}
	return (NULL);
}

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	int		diff;

	i = 0;
	while (i < n)
	{
		diff = *(unsigned char *)(s1 + i) - *(unsigned char *)(s2 + i);
		if (diff)
			return (diff);
		++i;
	}
	return (0);
}
