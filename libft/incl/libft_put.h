/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_put.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:49:23 by abronner          #+#    #+#             */
/*   Updated: 2025/06/19 17:27:30 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_PUT_H
# define LIBFT_PUT_H

# include "libft_str.h"

# include <unistd.h>

//	PUT

void		ft_putnbr_fd(int n, int fd);

void		ft_putendl_fd(const char *s, int fd);

void		ft_putstr_fd(const char *s, int fd);

void		ft_putchar_fd(const char c, int fd);

#endif
