/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_env.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:51:07 by abronner          #+#    #+#             */
/*   Updated: 2025/04/02 12:51:53 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_ENV_H
# define LIBFT_ENV_H

# include "libft_str.h"

extern char	**environ;

//	ENVIRON

char		**ft_splitpaths(const char *paths);

char		*ft_getenv(const char *name);

#endif
