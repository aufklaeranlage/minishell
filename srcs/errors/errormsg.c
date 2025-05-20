/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errormsg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:30:34 by abronner          #+#    #+#             */
/*   Updated: 2025/05/13 10:51:36 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

void	errormsg(char *obj, char *msg)
{
	ft_putstr_fd(SHNAME, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(obj, STDERR);
	ft_putstr_fd(": ", STDERR)
	ft_putstr_fd(msg, STDERR);
}
