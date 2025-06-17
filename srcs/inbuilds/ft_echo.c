/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:55:34 by akuzmin           #+#    #+#             */
/*   Updated: 2025/06/17 12:38:06 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inbuilds.h"
#include "expander.h"

int ft_echo(t_tokens *tokens, t_env *env)
{
	size_t i = 1;
	int new_line = 1;
	char *out;

	if (tokens->size == 1) { printf(""); return (0);}
	else if (tokens->size >= 2 && !ft_strncmp(tokens->content[1], "-n\0", 3))
		new_line = 0, i++;

	while (i < tokens->size)
	{
		out = ft_strdup("");
		if (tokens->type[i] == EXPAND_STR)
			out = ft_strjoin(out, expander(tokens->content[i], env, 0));
		else
			out = ft_strjoin(out, tokens->content[i]);
		
		printf("%s", out);
		if (i < tokens->size - 1)
			printf(" ");
		i++;
	}
	if (new_line)
	{
		printf("\n");
	}
	free(out);
	return (0);
}
