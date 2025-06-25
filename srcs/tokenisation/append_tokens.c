/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:44:00 by akuzmin           #+#    #+#             */
/*   Updated: 2025/06/25 19:05:49 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/tokenisation.h"

static void	join_tokens(t_tokens *out, t_tokens *t1, t_tokens *t2)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < t1->size)
	{
		out->content[i] = t1->content[i];
		out->type[i] = t1->type[i];
		i++;
	}
	j = 0;
	while (j < t2->size)
	{
		out->content[i + j] = t2->content[j];
		out->type[i + j] = t2->type[j];
		j++;
	}
	out->content[out->size] = NULL;
}

/**
 * @brief Add tokens in list of tokens
 * @param t1 pointer to original list of tokens
 * @param t2 appendable elements
 */
void	append_tokens(t_tokens **t1, t_tokens *t2)
{
	t_tokens	*out;

	out = malloc(sizeof(t_tokens));
	if (!out)
		return ;
	out->size = (*t1)->size + t2->size;
	out->content = malloc(sizeof(char *) * out->size + 1);
	out->type = malloc(sizeof(int) * out->size);
	if (!out->content || !out->type)
	{
		token_free(out);
		return ;
	}
	join_tokens(out, (*t1), t2);
	free(*t1);
	free(t2);
	*t1 = out;
}
