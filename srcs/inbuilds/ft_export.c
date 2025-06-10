/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:58:58 by akuzmin           #+#    #+#             */
/*   Updated: 2025/06/10 11:27:15 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inbuilds.h"

static int	export_flagcheck(t_token *tok);

//	tok is the token that contains the strings to insert. env is a pointer to
//	the local environment of the shell. exp is a pointer to the global
//	environment of the shell.
//	replaces already set variables in env with the new ones and 

int	ft_export(t_token *tok, t_env *env)
{
	int		ret;
	size_t	i;
	
	if (export_flagcheck(tok))
		return (1);
	
}

static int	export_flagcheck(t_token *tok)
{
	size_t	i;

	i = 1;
	while (i < tok->size)
	{
		if (tok->content[i][0] == '-')
		{
			if (tok->content[i][1] != 'p')
			{
				errormsg(SHNAME, "export", tok->content[i], "invalid option");
				ft_putstrfd(EXPUSE, 2)
				return (1);
			}
		}
		++i;
	}
	return (0);
}

static int	export_all(char ***env, char **exp)
{
	size_t	count;
	char	**tmp;

	count = ft_splitcount(*env);
	tmp = ft_splitlcpy(env, count);
	if (!tmp)
		return (1);

}
