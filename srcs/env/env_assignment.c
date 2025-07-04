/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_assignment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 11:34:34 by abronner          #+#    #+#             */
/*   Updated: 2025/07/04 18:43:42 by akuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "inbuilds.h"

static int	check_valid(char *str);

//	Assigns a variable to the environment after checking if it is valid
//	State can be set to either ENVSET, ENVEXP or ENVTMP
//		Returns 0 on success and 1 on invalid string and -1 on failure to
//		insert in the environment.

int	assign(char *str, int state, t_env *env)
{
	size_t	i;

	i = 0;
	if (check_valid(str))
		return (1);
	if (env_ins(str, state, env))
		return (-1);
	return (0);
}

//	Assigns all the valid strings starting at 0 as ENVTMP to the environment.
//	then cuts out the assigned strings from tok->content
//	TODO: OPTIMIZE BY USING DIFFERNT CUTSPLIT THAT REPLACES AND DOESNT USE STRDUP

int tmp_assign(t_tokens *tok, t_env *env)
{
	int		check;
	int		i;

	check = 0;
	i = 0;
	while (i < (int)tok->size)
	{
		if (tok->content[i][0] != '\0')
		{
			check = assign(tok->content[i], ENVTMP, env);
			if (check)
				break ;
		}
		++i;
	}
	if (!i)
		return (0);
	if (check == -1 || token_cut(tok, i, tok->size - 1))
		return (-1);
	return (0);
}

//	Checks if str starts with a valid variable name up till the first '=' or
//	the end of the string.
//		Returns 0 on success and 1 on fail.

static int	check_valid(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] != '_' && !ft_isalpha(str[i]))
		return (1);
	++i;
	while (str[i] != '=' && str[i] != '\0')
	{
		if (str[i] != '_' && !ft_isalnum(str[i]))
			return (1);
		++i;
	}
	if (str[i] == '=')
		return (0);
	return (1);
}
