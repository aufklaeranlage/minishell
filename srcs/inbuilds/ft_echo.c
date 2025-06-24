/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:55:34 by akuzmin           #+#    #+#             */
/*   Updated: 2025/06/24 15:53:56 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inbuilds.h"
#include "expander.h"

static int	echo_flag(char *str)
{
	size_t	i;

	if (!str)
		return (1);
	if (str[0] == '-' && str[1] == 'n')
	{
		i = 2;
		while (str[i] == 'n')
			i++;
		if (str[i] == '\0')
			return (0);
	}
	return (1);
}

int	ft_echo(t_tokens *tokens, t_env *env)
{
	size_t	i;
	int		new_line;

	i = 1;
	new_line = 0;
	(void)env;
	if (tokens->size == 1)
		return (write(STDOUT, "\n", 1), 0);
	if (tokens->size >= 2 && !echo_flag(tokens->content[1]))
		new_line = 1;
	while (i + new_line < tokens->size)
	{
		ft_putstr_fd(tokens->content[i + new_line], STDOUT);
		if (i + new_line < tokens->size - 1)
			ft_putstr_fd(" ", STDOUT);
		i++;
	}
	if (!new_line)
		ft_putstr_fd("\n", STDOUT);
	return (0);
}
