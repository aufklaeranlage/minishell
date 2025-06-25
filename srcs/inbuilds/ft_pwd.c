/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:58:58 by akuzmin           #+#    #+#             */
/*   Updated: 2025/06/25 15:30:08 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inbuilds.h"

int	ft_pwd(t_tokens *tok)
{
	char	*dir;

	if (tok->size > 1)
		return (errormsg(SHNAME, "pwd", "too many arguments", NULL), 1);
	dir = getcurdir();
	if (!dir)
		return (errormsg(SHNAME, "pwd", PWDNDT, NULL), 1);
	ft_putstr_fd(dir, STDOUT);
	ft_putchar_fd('\n', STDOUT);
	return (free(dir), 0);
}
