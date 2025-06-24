/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:58:58 by akuzmin           #+#    #+#             */
/*   Updated: 2025/06/24 10:55:47 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inbuilds.h"

int	ft_pwd(int fd)
{
	char	*dir;

	dir = getcurdir();
	if (!dir)
		return (errormsg(SHNAME, "pwd", PWDNDT, NULL), 1);
	ft_putstr_fd(dir, fd);
	ft_putchar_fd('\n', fd);
	return (free(dir), 0);
}
