/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errormsg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:30:34 by abronner          #+#    #+#             */
/*   Updated: 2025/06/10 11:18:34 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

void	errormsg(char *prog, char *obj, char *msg, char *opt)
{
	ft_putstr_fd(prog, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(obj, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(msg, STDERR);
	if (opt)
	{
		ft_putstr_fd(": ", STDERR);
		ft_putstr_fd(opt, STDERR);
	}
	ft_putchar_fd('\n', STDERR);
}
