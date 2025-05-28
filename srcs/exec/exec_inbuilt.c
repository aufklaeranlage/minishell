/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_inbuilts.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:31:56 by abronner          #+#    #+#             */
/*   Updated: 2025/05/27 15:32:45 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_inbuilt(t_group *group, char ***env)
{
	t_tokens *token;

	token = (t_tokens *)group->data;
	inbuilds(token, *env);
	return (0);
}
