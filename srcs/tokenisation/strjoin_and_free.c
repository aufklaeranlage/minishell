/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin_and_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:22:19 by akuzmin           #+#    #+#             */
/*   Updated: 2025/07/04 14:27:19 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenisation.h"
#include "expander.h"

/**
 * @brief Joins two strings and frees the first one.
 *
 * @param s1 First string, will be freed.
 * @param s2 Second string.
 * @return Newly allocated string containing the result of s1 + s2.
 */
char	*strjoin_and_free(char *s1, char *s2)
{
	char	*res;

	if (!s1)
		res = ft_strdup(s2);
	else if (!s2)
		res = ft_strdup(s1);
	else
		res = ft_strjoin(s1, s2);
	free(s1);
	return (res);
}
