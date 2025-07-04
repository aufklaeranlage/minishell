/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:58:58 by akuzmin           #+#    #+#             */
/*   Updated: 2025/07/04 13:22:57 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inbuilds.h"

int	ft_pwd(t_tokens *tok)
{
	char	*dir;

	(void)tok;
	dir = getcurdir();
	if (!dir)
		return (errormsg(SHNAME, "pwd", PWDNDT, NULL), 1);
	ft_putstr_fd(dir, STDOUT);
	ft_putchar_fd('\n', STDOUT);
	return (free(dir), 0);
}
