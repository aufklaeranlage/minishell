/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:58:58 by akuzmin           #+#    #+#             */
/*   Updated: 2025/06/23 17:38:36 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inbuilds.h"
#include "env.h"

static void	exp_print(t_env *env, int fd);

//	tok is the token that contains the strings to insert. env is a pointer to
//	the local environment of the shell. exp is a pointer to the global
//	environment of the shell.
//	replaces already set variables in env with the new ones and 

int	ft_export(t_tokens *tok, t_env *env, int fd)
{
	size_t	i;

	if (!tok || !env)
		return (1);
	if (tok->size == 1)
		return (exp_print(env, fd), 0);
	i = 1;
	while (i < tok->size)
		env_ins(tok->content[i++], ENVEXP, env);
	return (0);
}

static void	exp_print(t_env *env, int fd)
{
	t_list		*node;
	t_envnode	*envnode;

	if (!env || !env->wrap)
		return ;
	node = env->wrap->head;
	while (node)
	{
		envnode = (t_envnode *)node->content;
		if (envnode->state == ENVEXP)
		{
			ft_putstr_fd("export ", fd);
			ft_putstr_fd(envnode->var, fd);
			if (envnode->val)
			{
				ft_putstr_fd("=\"", fd);
				ft_putstr_fd(envnode->val, fd);
				ft_putchar_fd('"', fd);
			}
			ft_putchar_fd('\n', fd);
		}
		node = node->next;
	}
}
