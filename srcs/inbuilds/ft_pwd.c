/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:58:58 by akuzmin           #+#    #+#             */
/*   Updated: 2025/06/23 14:45:31 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inbuilds.h"

int	ft_pwd(void)
{
	char	*dir;

	dir = getcurdir();
	if (!dir)
		return (errormsg(SHNAME, "pwd", PWDNDT, NULL), 1);
	ft_putstr_fd(dir, 1);
	return (0);
}
