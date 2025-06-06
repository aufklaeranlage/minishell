/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_inbuilt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:31:56 by abronner          #+#    #+#             */
/*   Updated: 2025/05/28 16:13:02 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_inbuilt(t_group *grp, char ***env)
{
	t_tokens *token;

	token = (t_tokens *)grp->data;
	inbuilds(token, *env);
	return (0);
}
