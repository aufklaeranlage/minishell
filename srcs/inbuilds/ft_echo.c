/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:55:34 by akuzmin           #+#    #+#             */
/*   Updated: 2025/06/23 17:19:15 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inbuilds.h"
#include "expander.h"

static int echo_flag(char *str)
{
	size_t i;
	
    if (!str)
        return (1);
    if (str[0] == '-' && str[1] == 'n')
    {
        i = 2;
        while (str[i] == 'n')
            i++;
        return (str[i] == '\0' ? 0 : 1);
    }
    return (1);
}

int ft_echo(t_tokens *tokens, t_env *env, int fd)
{
	size_t i = 1;
	int new_line = 1;
	(void)env;
	 if (tokens->size == 1)
    {
        write(fd, "\n", 1);
        return (0);
    }
	if (tokens->size >= 2 && !echo_flag(tokens->content[1]))
    {
        new_line = 0;
        i++;
    }
	while (i < tokens->size)
	{	
		write(fd, tokens->content[i], ft_strlen(tokens->content[i]));
		if (i < tokens->size - 1)
			write(fd, " ", 2);
		i++;
	}
	if (new_line)
		write(fd, "\n", 1);
	return (0);
}
