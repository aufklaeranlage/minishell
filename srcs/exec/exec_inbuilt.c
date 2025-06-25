/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_inbuilt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:31:56 by abronner          #+#    #+#             */
/*   Updated: 2025/06/25 18:57:24 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_inbuilt(t_group *grp, t_env *env)
{
	if (handle_quotes((t_tokens *)grp->data, env))
		return (1);
	inbuilds(grp, env);
	return (0);
}
