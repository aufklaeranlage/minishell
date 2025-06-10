/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inbuilds.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:24:16 by akuzmin           #+#    #+#             */
/*   Updated: 2025/06/10 11:21:03 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INBUILDS_H
# define INBUILDS_H

# include "libft.h"
# include "tokenisation.h"

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>

# include <dirent.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# define EXPUSE "export: usage: export [name[=value] ...] or export [-p]\n"

// Inbuilds
int		inbuilds(t_tokens *tokens, char **env);

// and list of it
int		ft_echo(t_tokens *tokens, char **env);
int		ft_cd(t_tokens *tokens, char **env);
int		ft_pwd(void);
int		ft_env(char **env);
int		ft_unset(t_tokens *tokens, char ***env);
int		ft_export(char **env);
int		ft_exit(t_tokens *tokens, char **env);

// UTILS FOR USE OUTSIDE
char	*expand_path(char *str, char **env);

// Bonus
int		is_wildcard(char *str);
char	*expand_wildcard(char *str, char **env);

#endif
