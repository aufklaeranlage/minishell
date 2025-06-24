/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:58:58 by akuzmin           #+#    #+#             */
/*   Updated: 2025/06/24 15:59:33 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inbuilds.h"

int	ft_pwd(void)
{
	char	*dir;

	dir = getcurdir();
	if (!dir)
		return (errormsg(SHNAME, "pwd", PWDNDT, NULL), 1);
	ft_putstr_fd(dir, STDOUT);
	ft_putchar_fd('\n', STDOUT);
	return (free(dir), 0);
}
