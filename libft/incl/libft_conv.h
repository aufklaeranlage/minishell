/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_conv.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abronner <abronner@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:18:28 by abronner          #+#    #+#             */
/*   Updated: 2025/04/02 12:29:51 by abronner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_CONV_H
# define LIBFT_CONV_H

# include "libft_str.h"

# include <limits.h>

//	DEFINES

# define BASE "0123456789abcdefghijklmnopqrstuvw"

//	CONV

int			ft_atoi(const char *nptr);

char		*ft_itoa(int val);

//	STR TO LONG

long int	ft_strtol(const char *nptr, int base);

//	LONG TO STR

char		*ft_ltostr(long int val, int base);

#endif
