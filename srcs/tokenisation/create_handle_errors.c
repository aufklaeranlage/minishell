/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_handle_errors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:22:19 by akuzmin           #+#    #+#             */
/*   Updated: 2025/05/26 14:38:24 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/tokenisation.h"

// CASE: $() + CASE: "CMD | | | CMD" + "CMD | "
static int	prcr_c1(t_tokens *tokens, size_t i)
{
	if (i + 1 < tokens->size \
		&& tokens->content[i][0] == '$' && tokens->type[i + 1] == O_BR)
	{
		printf("zsh: parse error near '%s'. Handle it later!\n", \
			tokens->content[i]);
		return (1);
	}
	if (i + 1 < tokens->size \
		&& (tokens->type[i] >= BIN_AND && tokens->type[i] <= SMCLN) \
		&& (tokens->type[i + 1] >= BIN_AND && tokens->type[i + 1] <= SMCLN))
	{
		printf("zsh: parse error near '%s'\n", tokens->content[i + 1]);
		return (1);
	}
	if (i + 1 == tokens->size \
		&& (tokens->type[i] >= BIN_AND && tokens->type[i] <= SMCLN))
	{
		printf("zsh: parse error near '%s'\n", tokens->content[i]);
		return (1);
	}
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
			printf("zsh: parse error near '%s'\n", tokens->content[i + gap]);
			return (1);
		}
	}
	return (0);
}

static void	prcr_process(t_tokens *tokens, size_t *i, int *cmd_start)
{
	while (tokens->type[*i] >= RED_IN && tokens->type[*i] <= ADD_OUT \
		&& *i < tokens->size)
		(*i)++;
	if ((*cmd_start) == 0 && tokens->type[*i] >= INCMD_ECHO \
		&& tokens->type[*i] <= STD_CMD)
	{
		(*cmd_start) = 1;
		(*i)++;
	}
	while ((*cmd_start) == 1 && *i < tokens->size)
	{
		(*i)++;
		if ((tokens->type[*i] >= BIN_AND && tokens->type[*i] <= SMCLN) \
			|| tokens->type[*i] == O_BR)
			(*cmd_start) = 0;
	}
}

/**
SHOULD BE CASE: "CMD ARG | NOT_CMD"
if (cmd_start == 0 \
	&& (tokens->type[i] != ASSIGNMENT || tokens->type[i] != O_BR \
	|| !(tokens->type[i] >= INCMD_ECHO && tokens->type[i] <= STD_CMD)))
{
	printf("zsh: parse error near (CHECK) '%s'\n", tokens->content[i]);
	return (1);
}
*/
int	parser_input_validation(t_tokens *tokens)
{
	size_t	i;
	int		cmd_start;

	if (!tokens)
		return (1);
	i = 0;
	cmd_start = 0;
	while (i < tokens->size)
	{
		prcr_process(tokens, &i, &cmd_start);
		if (prcr_c1(tokens, i) || prcr_c2(tokens, i, cmd_start))
			return (1);
		i++;
	}
	return (0);
}
