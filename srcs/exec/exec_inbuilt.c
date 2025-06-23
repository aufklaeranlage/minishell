/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_inbuilt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:31:56 by abronner          #+#    #+#             */
/*   Updated: 2025/06/23 11:43:41 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_inbuilt(t_group *grp, t_env *env)
{
	t_tokens	*tok;

	tok = (t_tokens *)grp->data;
	inbuilds(tok, env);
	return (0);
}
