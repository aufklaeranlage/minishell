/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errormsg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:30:34 by abronner          #+#    #+#             */
/*   Updated: 2025/07/05 16:49:28 by akuzmin          ###   ########.fr       */
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

void	errormsg_parser(const char *msg)
{
	ft_putstr_fd(SHNAME, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd("syntax error near unexpected token `", STDERR);
	ft_putstr_fd(msg, STDERR);
	ft_putstr_fd("\'\n", STDERR);
}