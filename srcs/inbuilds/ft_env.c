/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:58:58 by akuzmin           #+#    #+#             */
/*   Updated: 2025/06/24 15:53:48 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inbuilds.h"

int	ft_env(t_env *env)
{
	size_t	i;

	if (!env)
		return (1);
	i = 0;
	while (env->arr[i])
	{
		ft_putstr_fd(env->arr[i], STDOUT);
		ft_putchar_fd('\n', STDOUT);
		++i;
	}
	return (0);
}
