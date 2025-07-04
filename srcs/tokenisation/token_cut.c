/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_cut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:26:01 by abronner          #+#    #+#             */
/*   Updated: 2025/06/26 16:48:20 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenisation.h"

static int	init_token_cut(char ***cont, int **type, size_t size);

//	Replaces a tokens content and type inplace. start and end are positions in
//	the token that are counted inclusive (they will be part of the changed
//	token).
//		RETURN: 0 on succes, 1 on failure

int	token_cut(t_tokens *tok, size_t start, size_t end)
{
	size_t	size;
	char	**newcont;
	int		*newtype;

	size = end - start + 2;
	if (init_token_cut(&newcont, &newtype, size))
		return (1);
	newcont[--size] = NULL;
	while (tok->size--)
	{
		if (tok->size < start || tok->size > end)
			free(tok->content[tok->size]);
		else
		{
			newcont[tok->size - start] = tok->content[tok->size];
			newtype[tok->size - start] = tok->type[tok->size];
		}
	}
	free(tok->content);
	tok->content = newcont;
	free(tok->type);
	tok->type = newtype;
	tok->size = size;
	return (0);
}

static int	init_token_cut(char ***cont, int **type, size_t size)
{
	*cont = malloc(size * sizeof(**cont));
	*type = malloc(size * sizeof(**type));
	if (!*cont || !*type)
		return (free(*cont), free(*type), 1);
	return (0);
}
