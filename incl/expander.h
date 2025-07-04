/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:43:55 by abronner          #+#    #+#             */
/*   Updated: 2025/06/30 13:29:04 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "libft.h"
# include "env.h"

# define VAR_DEL " <>|&$=+-\'\"\n"

char	*expander(char *str, t_env *env, size_t offset);
char	*expand_path(char *str, t_env *env);

//	NEW

int		split_expander(char *src, char ***dst, t_env *env);

char	**expander_main(const char *s, size_t total, size_t depth, t_env *env);

char	**tilde_expander(const char *str, size_t depth, t_env *env);

char	**param_expander(const char *s, size_t total, size_t depth, t_env *env);


//	UTILS

size_t	expander_skippre(const char *str);

#endif
