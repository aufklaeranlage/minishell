/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:29:27 by abronner          #+#    #+#             */
/*   Updated: 2025/06/23 11:32:41 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "expander.h"
#include "inbuilds.h"

extern char	**environ;

static void	exp_print(t_env *env);

int	main(void)
{
	t_env	*env;
	const char	*test[2] = {"ARG=ARG", NULL};
	char	*dir[3]	= {"cd\0", "/home\0", NULL};
	t_tokens	tok;

	tok.size = 2;
	tok.content = dir;

	env = env_init((const char **)environ);

	ft_env(env);

	ft_cd(&tok, env);

	ft_env(env);

	env_free(env);
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
			if (!envnode->val)
				ft_putstr_fd("export ", 1);
			ft_putstr_fd(envnode->var, 1);
			if (envnode->val)
			{
				ft_putstr_fd("=\"", 1);
				ft_putstr_fd(envnode->val, 1);
				ft_putchar_fd('"', 1);
			}
			ft_putchar_fd('\n', 1);
		}
		node = node->next;
	}
}
