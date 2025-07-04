/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:43:27 by abronner          #+#    #+#             */
/*   Updated: 2025/06/30 13:30:05 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"
#include "expander.h"

#include <stdio.h>

void	print_split(char **src);

int	main(int ac, char **av, char **envp)
{
	t_env	*env;
	char	**empty = NULL;

	if (!ac)
		return (1);
	env = env_init((const char **)envp);
	for (int i = 1; i < ac; i++)
	{
		split_expander(av[i], &empty, env);
		print_split(empty);
	}
	return (0);
}

void	print_split(char **src)
{
	size_t	i = 0;

	while(src[i])
	{
		printf("%zu: %s\n", i, src[i]);
		++i;
	}
}
