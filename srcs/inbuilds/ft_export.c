/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:58:58 by akuzmin           #+#    #+#             */
/*   Updated: 2025/06/11 11:00:44 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inbuilds.h"
#include "env.h"

static void	exp_print(t_env *env);

//	tok is the token that contains the strings to insert. env is a pointer to
//	the local environment of the shell. exp is a pointer to the global
//	environment of the shell.
//	replaces already set variables in env with the new ones and 

int	ft_export(t_token *tok, t_env *env)
{
	size_t	i;
	
	if (!tok || !env)
		return (1);
	if (tok->size == 1)
		return (exp_print(env), 0);
	i = 1;
	while (i < tok->size)
		env_insert(tok->content[i++]);
	return (0);
}

static void	exp_print(t_env *env)
{
	size_t	i;

	i = 0;
	while (i < env->size)
	{
		if (!env->val[i])
			ft_putstr_fd("export ", 1);
		ft_putstr_fd(env->var[i], 1);
		if (env->val[i])
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(env->val[i], 1);
			ft_putchar_fd('"', 1);
		}
		ft_putchar_fd('\n', 1);
		++i;
	}
}
