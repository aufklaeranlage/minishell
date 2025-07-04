/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inbuilds.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:24:16 by akuzmin           #+#    #+#             */
/*   Updated: 2025/06/26 16:13:08 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INBUILDS_H
# define INBUILDS_H

# include "libft.h"
# include "tokenisation.h"
# include "env.h"

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>

# include <dirent.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# define EXPUSE "export: usage: export [name[=value] ...] or export [-p]\n"

// and list of it
int		ft_echo(t_tokens *tokens, t_env *env);
int		ft_pwd(t_tokens *tok);
int		ft_env(t_env *env);
int		ft_unset(t_tokens *tok, t_env *env);
int		ft_export(t_tokens *tok, t_env *env);
void	ft_exit(void);

//	CD

int		ft_cd(t_tokens *tokens, t_env *env);

// Bonus
int		is_wildcard(char *str);
char	*expand_wildcard(char *str);

//	UTILS

char	*getcurdir(void);

//	HOME

int		tilde_exp(char **str, t_env *env);

int		tilde_ret(char **str, t_env *env);

char	*construct_prompt(t_env *env);

#endif
