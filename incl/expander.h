/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmin <akuzmin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:43:55 by abronner          #+#    #+#             */
/*   Updated: 2025/06/25 17:22:44 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "libft.h"
# include "env.h"

# define VAR_DEL " <>|&$=+-\'\"\n"

char	*expander(char *str, t_env *env, size_t offset);
char	*expand_path(char *str, t_env *env);

#endif
