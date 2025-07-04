/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_handle_errors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:22:19 by akuzmin           #+#    #+#             */
/*   Updated: 2025/07/04 18:07:10 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenisation.h"
#include "env.h"

// CASE: $() + CASE: "CMD | | | CMD" + "CMD | "
static int	prcr_c1(t_tokens *tokens, size_t i)
{
	if (i + 1 < tokens->size \
		&& tokens->content[i][0] == '$' && tokens->type[i + 1] == O_BR)
		return (errormsg(SHNAME, "syntax error near", \
			tokens->content[i], NULL), 2);
	if (i + 1 < tokens->size \
		&& (tokens->type[i] >= BIN_AND && tokens->type[i] <= OR) \
		&& (tokens->type[i + 1] >= BIN_AND && tokens->type[i + 1] <= OR))
		return (errormsg(SHNAME, "syntax error near", \
			tokens->content[i + 1], NULL), 2);
	if (i + 1 == tokens->size \
		&& (tokens->type[i] >= BIN_AND && tokens->type[i] <= OR))
		return (errormsg(SHNAME, "syntax error near", \
			tokens->content[i], NULL), 2);
	return (0);
}

// CASE: ASSIGNE (GROUP)
static int	prcr_c2(t_tokens *tokens, size_t i, int cmd_start)
{
	size_t	gap;

	gap = 0;
	while (i + gap < tokens->size \
		&& (tokens->type[i + gap] != O_BR && tokens->type[i + gap] != C_BR))
	{
		gap++;
		if (cmd_start == 0 && i + gap < tokens->size \
		&& (tokens->type[i] == ASSIGNMENT) \
		&& (tokens->type[i + gap] >= O_BR && tokens->type[i + gap] <= C_BR))
		{
			return (errormsg(SHNAME, "syntax error near", \
				tokens->content[i + gap], NULL), 1);
		}
	}
	return (0);
}

static int	prcr_c3(t_tokens *tokens, size_t i)
{
	while (i < tokens->size && tokens->type[i] != C_BR)
		i++;
	if (i + 1 < tokens->size && !(tokens->type[i + 1] >= SMCLN \
		&& tokens->type[i + 1] <= OR))
	{
		errormsg(SHNAME, "syntax error near", tokens->content[i + 1], NULL);
		return (1);
	}
	return (0);
}

static int	prcr_process(t_tokens *tokens, size_t *i, int *cmd_start)
{
	while ( *i < tokens->size && tokens->type[*i] >= RED_IN
		&& tokens->type[*i] <= ADD_OUT)
	{
		if (specifier_one(tokens->content[*i]))
			return (errormsg(SHNAME, "syntax error near unexpected token", \
				tokens->content[*i], NULL), 2);
		(*i)++;
	}
	if ((*cmd_start) == 0 && tokens->type[*i] >= INCMD_ECHO \
		&& tokens->type[*i] <= STD_CMD)
	{
		(*cmd_start) = 1;
		(*i)++;
		while ((*cmd_start) == 1 && *i < tokens->size)
		{
			if ((tokens->type[*i] >= BIN_AND && tokens->type[*i] <= OR) \
				|| tokens->type[*i] == O_BR)
				(*cmd_start) = 0;
			(*i)++;
		}
	}
	return (0);
}

/**
 * @brief Check is value valid or not
 * @param tokens 
 * @return int 0 - OK, 1 - KO
 */
int	parser_input_validation(t_tokens *tokens, t_shell *shell)
{
	size_t	i;
	int		cmd_start;
	int		is_error;

	if (!tokens)
		return (1);
	i = 0;
	cmd_start = 0;
	is_error = 0;
	while (i < tokens->size)
	{
		if (prcr_process(tokens, &i, &cmd_start) == 2)
			is_error = 2;
		if (prcr_c1(tokens, i) || prcr_c2(tokens, i, cmd_start) \
			|| prcr_c3(tokens, i))
			is_error = 2;
		i++;
	}
	shell->env->status = is_error;
	return (is_error);
}
