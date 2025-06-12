/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:43:55 by abronner          #+#    #+#             */
/*   Updated: 2025/06/11 16:42:14 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "libft.h"
# include "env.h"

# define VAR_DEL " <>|&$=+-\'\"\n"

char	*expander(char *str, t_env *env, size_t offset);

#endif
