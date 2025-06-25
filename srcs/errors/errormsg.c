/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errormsg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:30:34 by abronner          #+#    #+#             */
/*   Updated: 2025/06/25 11:19:08 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

void	errormsg(const char *prog, const char *obj, const char *msg,
const char *opt)
{
	ft_putstr_fd(prog, STDERR);
	if (obj)
	{
		ft_putstr_fd(": ", STDERR);
		ft_putstr_fd(obj, STDERR);
	}
	if (msg)
	{
		ft_putstr_fd(": ", STDERR);
		ft_putstr_fd(msg, STDERR);
	}
	if (opt)
	{
		ft_putstr_fd(": ", STDERR);
		ft_putstr_fd(opt, STDERR);
	}
	ft_putchar_fd('\n', STDERR);
}
