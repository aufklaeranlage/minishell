/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:55:34 by akuzmin           #+#    #+#             */
/*   Updated: 2025/06/12 10:56:31 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inbuilds.h"

/**
 * Need to add some garbage collector for all things
 */
int	ft_exit(t_tokens *tokens, t_env *env)
{
	(void)env;
	if (tokens)
		del_tokens(tokens);
	// if (env)
	// 	free(env);
	exit(0);
}
