/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_gnl.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@students.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:47:04 by abronner          #+#    #+#             */
/*   Updated: 2025/04/02 12:21:22 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

# include "libft_str.h"
# include "libft_list.h"

//	DEFINES

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 512
# endif

# define MAXFDS 64

char	*get_next_line(int fd);

#endif
