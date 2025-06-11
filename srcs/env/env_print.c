/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:28:47 by abronner          #+#    #+#             */
/*   Updated: 2025/06/11 13:03:40 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	env_print(t_env *env)
{
	size_t	i;

	if (!env)
		return (1);
	i = 0;
	while (env->arr[i])
	{
		ft_putstr_fd(env->arr[i], 1);
		ft_putchar_fd('\n', 1);
		++i;
	}
	return (0);
}
