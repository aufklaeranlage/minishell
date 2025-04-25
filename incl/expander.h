/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:43:55 by abronner          #+#    #+#             */
/*   Updated: 2025/04/25 16:16:37 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "libft.h"

# define VAR_DEL " <>|&$=+-\'\"\n"

char	*expander(char *str, char **env, size_t offset);

#endif
