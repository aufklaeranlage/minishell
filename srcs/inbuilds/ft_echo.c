/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:55:34 by akuzmin           #+#    #+#             */
/*   Updated: 2025/06/24 00:31:04 by akuzmin          ###   ########.fr       */
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

int	ft_echo(t_tokens *tokens, t_env *env, int fd)
{
	size_t	i;
	int		new_line;

	i = 1;
	new_line = 0;
	(void)env;
	if (tokens->size == 1)
		return (write(fd, "\n", 1), 0);
	if (tokens->size >= 2 && !echo_flag(tokens->content[1]))
		new_line = 1;
	while (i + new_line < tokens->size)
	{
		ft_putstr_fd(tokens->content[i + new_line], fd);
		if (i + new_line < tokens->size - 1)
			ft_putstr_fd(" ", fd);
		i++;
	}
	if (!new_line)
		ft_putstr_fd("\n", fd);
	return (0);
}
