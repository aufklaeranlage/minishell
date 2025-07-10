/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_handle_errors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:22:19 by akuzmin           #+#    #+#             */
/*   Updated: 2025/07/05 16:49:02 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "tokenisation.h"
#include "env.h"

static int	validation_nobrace(t_tokens *tok, size_t i);

static int	validation_noassign(t_tokens *tok, size_t i);

static int	validation_noexec(t_tokens *tok, size_t i);

static int	validation_newline(t_tokens *tok, size_t i, int err, \
	t_shell *shell);

//	LIST OF INVALID INPUTS:
//		<NONE>	| / || / &&
//		| / || / && <NL>
//		<ASSIGNMENT> '('
//		')' <ASSIGNMENT> [| / || / && / ;]
//		Unclosed " or '
//

int	parser_input_validation(t_tokens *tok, t_shell *shell)
{
	size_t	i;
	int		err;

	if (!tok)
		return (1);
	if (tok->size == 0)
		return (0);
	i = 0;
	err = 0;
	if (tok->type[0] >= PIPE && tok->type[0] <= OR)
		err = 1;
	while (i < tok->size && !err)
	{
		if (tok->type[i] == ASSIGNMENT)
			err = validation_nobrace(tok, ++i);
		else if (tok->type[i] == C_BR)
			err = validation_noassign(tok, ++i);
		else if (tok->type[i] >= PIPE && tok->type[i] <= OR)
			err = validation_noexec(tok, ++i);
		else
			++i;
	}
	return (validation_newline(tok, i, err, shell));
}

//	Takes a token for safety check.

static int	validation_nobrace(t_tokens *tok, size_t i)
{
	if (i >= tok->size)
		return (0);
	if (tok->type[i] == O_BR)
		return (1);
	return (0);
}

//	Takes a token for safety check.

static int	validation_noassign(t_tokens *tok, size_t i)
{
	if (i >= tok->size)
		return (0);
	if (tok->type[i] == ASSIGNMENT)
		return (1);
	return (0);
}

//	Takes a token for safety check.

static int	validation_noexec(t_tokens *tok, size_t i)
{
	if (i >= tok->size)
		return (0);
	if (tok->type[i] >= PIPE && tok->type[i] <= OR)
		return (1);
	return (0);
}

static int	validation_newline(t_tokens *tok, size_t i, int err, t_shell *shell)
{
	if (i == tok->size) 
		if (tok->type[i - 1] >= PIPE && tok->type[i - 1] <= OR)
			err = 1;
	if (err)
	{
		shell->env->status = 2;
		if (i == tok->size)
			errormsg_parser("newline");
		else
			errormsg_parser(tok->content[i]);
	}
	return (err);
}
