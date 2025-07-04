/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:58:58 by akuzmin           #+#    #+#             */
/*   Updated: 2025/07/04 13:36:19 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inbuilds.h"
#include "env.h"

static int	check_valid(char *str);

static void	exp_print(t_env *env);

//	tok is the token that contains the strings to insert. env is a pointer to
//	the local environment of the shell. exp is a pointer to the global
//	environment of the shell.
//	replaces already set variables in env with the new ones and 

int	ft_export(t_tokens *tok, t_env *env)
{
	int		ret;
	size_t	i;

	if (!tok || !env)
		return (1);
	if (tok->size == 1)
		return (exp_print(env), 0);
	i = 1;
	while (i < tok->size)
	{
		ret = check_valid(tok->content[i]);
		if (!ret)
			env_ins(tok->content[i], ENVEXP, env);
		++i;
	}
	return (ret);
}

static int	check_valid(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (errormsg(SHNAME, "export", str, "not a valid identifier"), 1);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (errormsg(SHNAME, "export", str, "not a valid identifier"),
		   1);
		++i;
	}
	if (str[i] == '=' && i == 1)
		return (errormsg(SHNAME, "export", str, "not a valid identifier"), 1);
	return (0);
}

static void	exp_print(t_env *env)
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
			ft_putstr_fd("export ", STDOUT);
			ft_putstr_fd(envnode->var, STDOUT);
			if (envnode->val)
			{
				ft_putstr_fd("=\"", STDOUT);
				ft_putstr_fd(envnode->val, STDOUT);
				ft_putchar_fd('"', STDOUT);
			}
			ft_putchar_fd('\n', STDOUT);
		}
		node = node->next;
	}
}
