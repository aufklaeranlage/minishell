/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:55:34 by akuzmin           #+#    #+#             */
/*   Updated: 2025/07/04 14:12:40 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inbuilds.h"
#include "exec.h"

static int	check_valid(char *str);

int	ft_exit(t_tokens *tok, t_group *grp)
{
	int		ret;

	if (!grp)
		return (1);
	ft_putstr_fd("exit\n", 1);
	if (tok->size > 2)
		return (errormsg(SHNAME, "exit", "too many arguments", NULL), 1);
	ret = 2;
	if (tok->size == 2 && check_valid(tok->content[1]))
		errormsg(SHNAME, "exit", tok->content[1], "numeric argument required");
	else
		ret = ft_atoi(tok->content[1]);
	exec_cleanup(grp->shell);
	exit(ret);
}

static int	check_valid(char *str)
{
	size_t	i;

	i = 0;
	while (ft_isspace(str[i]))
		++i;
	if (str[i] == '+' || str[i] == '-')
		++i;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		++i;
	}
	return (0);
}
