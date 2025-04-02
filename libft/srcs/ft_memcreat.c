/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcreat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@students.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:43:15 by abronner          #+#    #+#             */
/*   Updated: 2025/04/02 12:37:55 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mem.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*out;
	size_t	total;

	if (SIZE_MAX / nmemb < size)
		return (NULL);
	if (nmemb == 0 || size == 0)
		total = sizeof(char);
	else
		total = nmemb * size;
	out = malloc(total);
	if (out)
		ft_bzero(out, total);
	return (out);
}
