/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 23:34:40 by akuzmin           #+#    #+#             */
/*   Updated: 2025/06/23 23:40:02 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenisation.h"
#include "minichill.h"

/**
 * @brief Frees all memory allocated for the t_tokens structure.
 * Frees the `content` array, the `type` array, 
 * and the t_tokens structure itself.
 * @param out Pointer to the t_tokens structure to be freed.
 * @return Always returns NULL to simplify error handling in return statements.
 */
void	*del_tokens(t_tokens *out)
{
	size_t	i;

	i = 0;
	if (!out)
		return (NULL);
	if (out->content)
	{
		while (i < out->size && out->content[i])
			free(out->content[i++]);
		free(out->content);
	}
	if (out->type)
		free(out->type);
	free(out);
	return (NULL);
}
