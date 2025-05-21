/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errormsg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:30:34 by abronner          #+#    #+#             */
/*   Updated: 2025/05/21 11:23:23 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

void	errormsg(char *obj, char *msg)
{
	ft_putstr_fd(SHNAME, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(obj, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(msg, STDERR);
	ft_putchar_fd('\n', STDERR);
}
