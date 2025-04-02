/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_mem.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:34:35 by abronner          #+#    #+#             */
/*   Updated: 2025/04/02 16:18:28 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MEM_H
# define LIBFT_MEM_H

# include "libft_ctype.h"

# include <stdlib.h>
# include <stdint.h>

//	MEM SEARCH

void	*ft_memchr(const void *dest, int c, size_t n);

void	*ft_memrchr(const void *dest, int c, size_t n);

int		ft_memcmp(const void *s1, const void *s2, size_t n);

//	MEM CHANGE

void	*ft_memset(void *s, int c, size_t n);

void	ft_bzero(void *s, size_t n);

void	*ft_memcpy(void *dest, const void *src, size_t n);

void	*ft_memmove(void *dest, const void *src, size_t n);

//	MEM CREATE

void	*ft_calloc(size_t nmemb, size_t size);

#endif
